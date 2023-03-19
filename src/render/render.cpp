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
#include <simulation/components.h>

#include <entt/entt.hpp>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cstring>
#include <sstream>

using namespace cv::render;

RenderManager::RenderManager(entt::registry& registry)
    : m_EnTTRegistry(registry)
{}

RenderManager::~RenderManager() {}

int
RenderManager::Init()
{
    m_log = std::make_unique<core::Log>("RenderManager.log");

    // open window
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);
    m_window = SDL_CreateWindow("CubeVoid",
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                640,
                                480,
                                SDL_WINDOW_OPENGL);
    if (!m_window) {
        return -1;
    }

    m_context = SDL_GL_CreateContext(m_window);
    if (!m_context) {
        return -1;
    }

    SDL_GL_SetSwapInterval(1);
    m_log->Write("GLFW Success\n");
    // init glew and check for success
    if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
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
RenderManager::Quit()
{
    SDL_DestroyWindow(m_window);
    return 0;
}

int
RenderManager::Render(const engine::Clock::DurationT& deltaTime)
{
    std::chrono::milliseconds thirtyFPS(33);
    std::chrono::seconds secondsPerRotation(10);

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
        for (auto entity :
             m_EnTTRegistry
                 .view<component::Light, sim::component::Position>()) {
            auto& [light, pos] =
                m_EnTTRegistry.get<component::Light, sim::component::Position>(
                    entity);

            GLuint La =
                glGetUniformLocation(m_shaderProgram->GetId(), "Light.La");
            GLuint Ld =
                glGetUniformLocation(m_shaderProgram->GetId(), "Light.Ld");
            GLuint Ls =
                glGetUniformLocation(m_shaderProgram->GetId(), "Light.Ls");
            GLuint Pos = glGetUniformLocation(m_shaderProgram->GetId(),
                                              "Light.Position");

            glUniform3fv(La, 1, glm::value_ptr(light.La));
            glUniform3fv(Ld, 1, glm::value_ptr(light.Ld));
            glUniform3fv(Ls, 1, glm::value_ptr(light.Ls));

            // get position in camera space
            glm::vec4 position = view * glm::vec4(pos.position, 1);
            glUniform4fv(Pos, 1, glm::value_ptr(position));
        }

        for (auto entity :
             m_EnTTRegistry.view<component::Mesh, component::Material>()) {
            // set material uniforms before drawing
            auto& material = m_EnTTRegistry.get<component::Material>(entity);

            GLuint Ka =
                glGetUniformLocation(m_shaderProgram->GetId(), "Material.Ka");
            GLuint Kd =
                glGetUniformLocation(m_shaderProgram->GetId(), "Material.Kd");
            GLuint Ks =
                glGetUniformLocation(m_shaderProgram->GetId(), "Material.Ks");

            glUniform3fv(Ka, 1, glm::value_ptr(material.Ka));
            glUniform3fv(Kd, 1, glm::value_ptr(material.Kd));
            glUniform3fv(Ks, 1, glm::value_ptr(material.Ks));

            m_EnTTRegistry.get<component::Mesh>(entity).mesh.Draw();
        }

        SDL_GL_SwapWindow(m_window);
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
    int w;
    int h;
    SDL_GetWindowSize(m_window, &w, &h);
    return (float)w / h;
}
