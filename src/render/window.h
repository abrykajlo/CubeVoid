#pragma once

#include "rect.h"

#include <SDL.h>

namespace cv {
namespace render {
class Window {
  public:
    Window();
    ~Window();

    int Init();
    void Swap() const;
    SDL_Window* Get() const;
    const Rect& GetRect() const;

  private:
    SDL_Window* m_window;
};
}
}