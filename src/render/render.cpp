/* Copyright (C) 2017, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/

#include "render.h"

#include <core/file.h>
#include <core/log.h>
#include <core/math.h>
#include <render/components.h>
#include <render/shader_program.h>
#include <render/window.h>
#include <simulation/components.h>

#include <entt/entt.hpp>
#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cstring>
#include <sstream>

using namespace cv::render;

RenderManager::RenderManager(const Window& window, entt::registry& registry)
    : m_window(window)
    , m_EnTTRegistry(registry)
{}

RenderManager::~RenderManager() {}

int
RenderManager::Init()
{
    m_log = std::make_unique<core::Log>("RenderManager.log");

    SDL_GL_SetSwapInterval(1);
    m_log->Write("SDL Success\n");
    // init glew and check for success
    if (!gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress)) {
        m_log->Write("GLAD failed to initialize\n");
        return -1;
    }
    m_log->Write("GLAD initialized\n");

    glViewport(0, 0, 640, 480);
    glClearColor(0.5, 0.5, 0.5, 1);

    if (InitShaders() < 0) {
        m_log->Write("Failed to initialize shaders\n");
        return -1;
    }
    m_log->Write("Shaders initialized\n");

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);

    return 0;
}

int
RenderManager::Render(const engine::Clock::DurationT& deltaTime)
{
    std::chrono::milliseconds thirtyFPS(33);

    if (m_timeSinceLastRender >= thirtyFPS) {
        m_timeSinceLastRender = engine::Clock::DurationT(0);
        // clear buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // set camera view
        Camera mainCamera = GetMainCamera();
        mat4 view = mainCamera.View();
        glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(view));

        // set projection
        mat4 proj = mainCamera.Projection();
        glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(proj));

        // set normal matrix
        glm::mat3 normMat = glm::inverseTranspose(glm::mat3(view));
        glUniformMatrix3fv(2, 1, GL_FALSE, glm::value_ptr(normMat));

        // setup point light
        const auto& lightView =
            m_EnTTRegistry
                .view<component::PBRLight, sim::component::Position>();
        int i = 0;
        for (const auto lightId : lightView) {
            char buf[32];
            sprintf(buf, "Light[%d].L", i);
            GLuint L = glGetUniformLocation(m_shaderProgram->GetId(), buf);

            sprintf(buf, "Light[%d].Position", i);
            GLuint Pos = glGetUniformLocation(m_shaderProgram->GetId(), buf);

            entt::handle lightEntity(m_EnTTRegistry, lightId);
            auto& [light, pos] =
                lightEntity
                    .get<component::PBRLight, sim::component::Position>();
            glUniform3fv(L, 1, glm::value_ptr(light.L));
            // get position in camera space
            glm::vec4 position = view * glm::vec4(pos.position, 1);
            glUniform4fv(Pos, 1, glm::value_ptr(position));

            if (++i >= 3) {
                break;
            }
        }

        for (auto entity :
             m_EnTTRegistry.view<component::Mesh, component::PBRMaterial>()) {
            // set material uniforms before drawing
            auto& material = m_EnTTRegistry.get<component::PBRMaterial>(entity);

            GLuint Color = glGetUniformLocation(m_shaderProgram->GetId(),
                                                "Material.Color");
            GLuint Metal = glGetUniformLocation(m_shaderProgram->GetId(),
                                                "Material.Metal");
            GLuint Roughness = glGetUniformLocation(m_shaderProgram->GetId(),
                                                    "Material.Roughness");

            glUniform3fv(Color, 1, glm::value_ptr(material.Color));
            glUniform1i(Metal, material.Metal);
            glUniform1f(Roughness, material.Roughness);

            m_EnTTRegistry.get<component::Mesh>(entity).mesh.Draw();
        }

        m_window.Swap();
    } else {
        m_timeSinceLastRender += deltaTime;
    }
    return 0;
}

int
RenderManager::InitShaders()
{
    m_log->Write("Initializing Shaders\n");
    DefaultReadFile vertShaderFile;
    if (vertShaderFile.Open("./assets/shaders/vertex.glsl") < 0) {
        m_log->Write("Failed to open vertex shader file\n");
        return -1;
    }
    DefaultReadFile fragShaderFile;
    if (fragShaderFile.Open("./assets/shaders/fragment.glsl") < 0) {
        m_log->Write("Failed to open fragment shader file\n");
        return -1;
    }

    Shader vertShader(VERTEX_SHADER);
    Shader fragShader(FRAGMENT_SHADER);

    // prepare shader sources
    char buf[2048];
    memset(buf, 0, sizeof(buf));
    vertShaderFile.Read(buf, sizeof(buf));
    vertShader.SetSource(buf);
    if (vertShader.Compile() < 0) {
        m_log->Write(vertShader.GetError());
        return -1;
    }
    m_log->Write("Vertex Shader compiled successfully\n");

    memset(buf, 0, sizeof(buf));
    fragShaderFile.Read(buf, sizeof(buf));
    fragShader.SetSource(buf);
    if (fragShader.Compile() < 0) {
        m_log->Write(fragShader.GetError());
        return -1;
    }
    m_log->Write("Fragment Shader compiled successfully\n");

    // set up shaderprogram
    m_shaderProgram = std::make_unique<ShaderProgram>();
    m_shaderProgram->AttachShader(vertShader);
    m_shaderProgram->AttachShader(fragShader);
    if (m_shaderProgram->Link() < 0) {
        m_log->Write(m_shaderProgram->GetError());
        return -1;
    }
    m_log->Write("Shader program linked successfully\n");

    m_shaderProgram->Use();
    return 0;
}

Camera
RenderManager::GetMainCamera()
{
    float aspectRatio = GetAspectRatio();
    entt::handle cameraEntity(m_EnTTRegistry,
                              m_EnTTRegistry.view<component::MainCamera>()[0]);
    const auto [camera, pos, rot] =
        cameraEntity.try_get<component::MainCamera,
                             sim::component::Position,
                             sim::component::Rotation>();
    Camera rendererCamera(
        camera->fovy, aspectRatio, camera->zNear, camera->zFar);

    if (pos) {
        rendererCamera.SetEye(pos->position);
    }

    if (rot) {
        rendererCamera.SetOrientation(rot->rotation);
    }

    return rendererCamera;
}

float
RenderManager::GetAspectRatio()
{
    Window::Size size = m_window.GetSize();
    return (float)size.w / size.h;
}
