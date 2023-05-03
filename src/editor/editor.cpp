#include "editor.h"

#include <SDL.h>
#include <glad/glad.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_opengl3.h>

cv::editor::Editor::Editor() {}

cv::editor::Editor::~Editor() {}

int
cv::editor::Editor::Init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return -1;
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
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
    if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
        return -1;
    }

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    if (!ImGui_ImplSDL2_InitForOpenGL(m_window, m_context)) {
        return -1;
    }

    if (!ImGui_ImplOpenGL3_Init()) {
        return -1;
    }

    return 0;
}

int
cv::editor::Editor::Quit()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    SDL_GL_DeleteContext(m_context);
    SDL_DestroyWindow(m_window);
    SDL_Quit();

    return 0;
}

int
cv::editor::Editor::Run()
{
    const ImGuiIO& io = ImGui::GetIO();

    bool quit = false;
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }

            ImGui_ImplSDL2_ProcessEvent(&event);
        }

        ImGui_ImplSDL2_NewFrame();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

        ImGui::Begin("Hello World");
        if (ImGui::Button("Quit")) {
            quit = true;
        }
        ImGui::End();
        ImGui::EndFrame();

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

        SDL_GL_SwapWindow(m_window);
    }

    return 0;
}
