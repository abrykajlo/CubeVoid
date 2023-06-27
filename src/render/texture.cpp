#include "texture.h"

using namespace cv::render;

Texture::Texture()
    : Texture({ 0, 0 })
{
}

cv::render::Texture::Texture(const Rect& rect)
    : m_rect(rect)
{
    UpdateStorage();
}

Texture::~Texture() {}

const Rect&
cv::render::Texture::GetRect()
{
    return m_rect;
}

void
cv::render::Texture::SetRect(const Rect& rect)
{
    if (m_rect != rect) {
        m_rect = rect;
        UpdateStorage();
    }
}

void
cv::render::Texture::UpdateStorage()
{
    Bind();
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, m_rect.x, m_rect.y);
}
