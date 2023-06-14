#pragma once

#include <render/texture.h>

#include <glad/gl.h>

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