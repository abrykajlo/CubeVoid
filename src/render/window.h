#pragma once

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

    struct Size
    {
        int w;
        int h;
    };
    Size GetSize() const;

  private:
    SDL_Window* m_window;
};
}
}