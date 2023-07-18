#include "texture.h"

using namespace cv::render::gl;

Texture::Texture()
    : Texture({ 0, 0 })
{
}

Texture::Texture(const Rect& rect)
    : m_rect(rect)
{
    UpdateStorage();
}

Texture::~Texture() {}

const cv::render::Rect&
Texture::GetRect()
{
    return m_rect;
}

void
Texture::SetRect(const Rect& rect)
{
    if (m_rect != rect) {
        m_rect = rect;
        UpdateStorage();
    }
}

void
Texture::UpdateStorage()
{
    Bind();
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, m_rect.x, m_rect.y);
}
