/* Copyright (C) 2017, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/

#include "render.h"

#include <core/file.h>
#include <core/log.h>
#include <core/math.h>
#include <render/shader_program.h>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cstring>
#include <sstream>

static void
error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

RenderManager::RenderManager() {}

RenderManager::~RenderManager() {}

RenderManager&
RenderManager::GetInstance()
{
    static std::unique_ptr<RenderManager> s_renderManager = nullptr;
    if (s_renderManager == nullptr) {
        s_renderManager = std::make_unique<RenderManager>();
    }
    return *s_renderManager.get();
}

int
RenderManager::Init()
{
    m_log = std::make_unique<Log>("RenderManager.log");

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

    // DefaultReadFile meshFile;
    // meshFile.Open("./assets/models/dragon.obj");

    // auto size = meshFile.Size();
    // char* fileContents = new char[size];
    // meshFile.Read(fileContents, size);
    // std::istringstream fileContentStream(std::string(fileContents, size));

    // if (!Parse(fileContentStream, m_mesh)) {
    //     m_log->Write("unable to parse file");
    //     return -1;
    // }
    // delete[] fileContents;
    MakeCube(m_mesh, 1.0f);
    m_mesh.Init();

    m_lastTime = m_clock.now();
    m_initialized = true;

    return 0;
}

int
RenderManager::Quit()
{
    SDL_DestroyWindow(m_window);
    m_mesh.Quit();
    return 0;
}

int
RenderManager::Render()
{
    auto now = m_clock.now();
    auto timeSinceLast = now - m_lastTime;
    std::chrono::milliseconds thirtyFPS(33);
    std::chrono::seconds secondsPerRotation(10);

    if (timeSinceLast >= thirtyFPS) {
        // clear buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // set camera view
        mat4 view = m_mainCamera.View();
        glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(view));

        // set projection
        mat4 proj = m_mainCamera.Projection();
        glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(proj));

        // set normal matrix
        glm::mat3 normMat = glm::inverseTranspose(glm::mat3(view));
        glUniformMatrix3fv(2, 1, GL_FALSE, glm::value_ptr(normMat));

        m_mesh.Draw();
        SDL_GL_SwapWindow(m_window);
        m_lastTime = now;
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
    char buf[1024];
    memset(buf, 0, 1024);
    vertShaderFile.Read(buf, 1024);
    vertShader.SetSource(buf);
    if (vertShader.Compile() < 0) {
        m_log->Write(vertShader.GetError());
        return -1;
    }
    m_log->Write("Vertex Shader compiled successfully\n");

    memset(buf, 0, 1024);
    fragShaderFile.Read(buf, 1024);
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
