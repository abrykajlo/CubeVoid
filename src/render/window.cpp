#include "window.h"

using namespace cv::render;

Window::Window() {}

Window::~Window()
{
    SDL_DestroyWindow(m_window);
}

int
Window::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return -1;
    }

    m_window = SDL_CreateWindow("CubeVoid",
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                640,
                                480,
                                SDL_WINDOW_OPENGL);
    if (!m_window) {
        return -1;
    }

    return 0;
}

void
Window::Swap() const
{
    SDL_GL_SwapWindow(m_window);
}

SDL_Window*
Window::Get() const
{
    return m_window;
}

Window::Size
Window::GetSize() const
{
    int w, h;
    SDL_GetWindowSize(m_window, &w, &h);
    return Size{ w, h };
}
