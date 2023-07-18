#pragma once

#include "gl.h"

namespace cv {
namespace render {
namespace gl {
class RenderBuffer;
class Texture;
class FrameBuffer : public GLObject<FrameBuffer>
{
  public:
    FrameBuffer();
    virtual ~FrameBuffer();

    void AttachTexture(const Texture& tex);
    void AttachDepthBuffer(const RenderBuffer& renderBuf);
};

template<>
struct GLTraits<FrameBuffer>
{
    static void gen(GLuint& id) { glGenFramebuffers(1, &id); }
    static void del(const GLuint id) { glDeleteFramebuffers(1, &id); }
    static void bind(const GLuint id) { glBindFramebuffer(GL_FRAMEBUFFER, id); }
};
}
}
}
