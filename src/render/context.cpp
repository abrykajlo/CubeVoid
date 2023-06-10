#include "context.h"

#include <render/window.h>

using namespace cv::render;

Context::Context(const Window& window, int majorVersion, int minorVersion)
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, majorVersion);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minorVersion);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);
    m_context = SDL_GL_CreateContext(window.Get());
}

Context::~Context()
{
    SDL_GL_DeleteContext(m_context);
}

bool
Context::Valid() const
{
    return m_context;
}

SDL_GLContext
Context::Get() const
{
    return m_context;
}
