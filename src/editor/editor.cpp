#include "editor.h"

#include <render/components.h>

#include <SDL.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_sdl2.h>
#include <glad/glad.h>

using namespace cv::editor;

Editor::Editor() {}

Editor::~Editor() {}

int
Editor::Init()
{
    if (m_window.Init() < 0) {
        return -1;
    }

    m_context = std::make_unique<render::Context>(m_window, 4, 5);
    if (!m_context->Valid()) {
        return -1;
    }

    entt::handle camHandle(m_entityRegistry, m_entityRegistry.create());
    camHandle.emplace<cv::render::component::MainCamera>(
        glm::radians(45.f), 0.1f, 100.f);

    m_renderManager =
        std::make_unique<render::RenderManager>(m_window, m_entityRegistry);
    if (m_renderManager->Init() < 0) {
        return -1;
    }
    m_frameBuffer = std::make_unique<render::FrameBuffer>();
    m_texture = std::make_unique<render::Texture>(400, 400);

    SDL_GL_SetSwapInterval(1);
    if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
        return -1;
    }

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    if (!ImGui_ImplSDL2_InitForOpenGL(m_window.Get(), m_context->Get())) {
        return -1;
    }

    if (!ImGui_ImplOpenGL3_Init()) {
        return -1;
    }

    return 0;
}

int
Editor::Quit()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    SDL_Quit();

    return 0;
}

int
Editor::Run()
{
    bool done = false;
    while (!done) {
        m_clock.Start();
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                done = true;
            }

            ImGui_ImplSDL2_ProcessEvent(&event);
        }

        ImGui_ImplSDL2_NewFrame();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
        EditorWindow();
        ImGui::EndFrame();
        Render();
        m_clock.Stop();
    }

    return 0;
}

void
Editor::EditorWindow()
{
    m_texture->Bind();
    m_frameBuffer->Bind();
    m_renderManager->Render(m_clock.GetTimeDelta());
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    ImGui::Begin("Editor");
    ImGui::Image((void*)m_texture->GetId(),
                 ImVec2(m_texture->GetWidth(), m_texture->GetHeight()));
    ImGui::End();
}

void
Editor::Render()
{
    const ImGuiIO& io = ImGui::GetIO();

    ImGui::Render();
    glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // render additional platform windows
    SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
    SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    SDL_GL_MakeCurrent(backup_current_window, backup_current_context);

    m_window.Swap();
}
