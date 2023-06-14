#pragma once

#include <glad/gl.h>

#include <cstdint>

namespace cv {
namespace render {
class Texture
{
  public:
    Texture(size_t width, size_t height);
    ~Texture();

    void Bind() const;
    GLuint GetId() const;
    size_t GetWidth() const;
    size_t GetHeight() const;

  private:
    GLuint m_tid;
    size_t m_width;
    size_t m_height;
};
}
}