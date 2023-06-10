#include "texture.h"

using namespace cv::render;

Texture::Texture(size_t width, size_t height)
    : m_width(width)
    , m_height(height)
{
    glGenTextures(1, &m_tid);
    Bind();
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, m_width, m_height);
}

Texture::~Texture() {
    glDeleteTextures(1, &m_tid);
}

void
cv::render::Texture::Bind() const
{
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_tid);
}

GLuint
cv::render::Texture::GetId() const
{
    return m_tid;
}

size_t
cv::render::Texture::GetWidth() const
{
    return m_width;
}

size_t
cv::render::Texture::GetHeight() const
{
    return m_height;
}
