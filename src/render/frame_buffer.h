#pragma once

#include <render/texture.h>

#include <glad/glad.h>

namespace cv {
namespace render {
class FrameBuffer
{
  public:
    FrameBuffer();
    ~FrameBuffer();

    void AttachTexture(const Texture& tex);
    void Bind();

private:
    GLuint m_fbo = 0;
};
}
}