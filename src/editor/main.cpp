#include <SDL.h>
#undef main
#include <glad/glad.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_opengl3.h>

int
main()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return -1;
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_Window* window = SDL_CreateWindow("CubeVoid",
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                640,
                                480,
                                SDL_WINDOW_OPENGL);
    if (!window) {
        return -1;
    }

    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (!context) {
        return -1;
    }

    SDL_GL_SetSwapInterval(1);
    if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
        return -1;
    }

    ImGui::CreateContext();
    if (!ImGui_ImplSDL2_InitForOpenGL(window, context)) {
        return -1;
    }

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
        ImGui::NewFrame();

        ImGui::Begin("Hello World");
        if (ImGui::Button("Quit")) {
            quit = true;
        }
        ImGui::End();
        ImGui::EndFrame();
    }

    ImGui_ImplSDL2_Shutdown();
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}