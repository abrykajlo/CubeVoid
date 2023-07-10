#pragma once

#include <SDL.h>

namespace cv {
namespace render {
class Window;
class Context
{
  public:
    Context(const Window& window, int majorVersion, int minorVersion);
    ~Context();

    bool Valid() const;
    SDL_GLContext Get() const;

  private:
    SDL_GLContext m_context;
};
}
}