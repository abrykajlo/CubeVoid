#pragma once

#include <SDL.h>

#include <engine/game.h>

namespace cv {
namespace editor {
class Editor
{
  public:
    Editor();
    ~Editor();

    int Init();
    int Quit();
    int Run();

  private:
    engine::Game m_game;
    SDL_Window* m_window;
    SDL_GLContext m_context;
};
}
}