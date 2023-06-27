#pragma once

#include <render/gl_object.h>

#include <glad/gl.h>

namespace cv {
namespace render {
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
struct GLObjectTraits<FrameBuffer>
{
    static void gen(GLuint& id) { glGenFramebuffers(1, &id); }
    static void del(const GLuint id) { glDeleteFramebuffers(1, &id); }
    static void bind(const GLuint id) { glBindFramebuffer(GL_FRAMEBUFFER, id); }
};
}
}
