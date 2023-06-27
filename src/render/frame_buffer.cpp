#include "frame_buffer.h"

#include "render_buffer.h"
#include "texture.h"

using namespace cv::render;

FrameBuffer::FrameBuffer()
    : GLObject()
{
}

FrameBuffer::~FrameBuffer() {}

void
FrameBuffer::AttachTexture(const Texture& tex)
{
    Bind();
    glFramebufferTexture2D(
        GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex.GetId(), 0);
    GLenum drawBufs = GL_COLOR_ATTACHMENT0;
    glDrawBuffers(1, &drawBufs);
}

void
FrameBuffer::AttachDepthBuffer(const RenderBuffer& renderBuf)
{
    Bind();
    glFramebufferRenderbuffer(GL_FRAMEBUFFER,
                              GL_DEPTH_ATTACHMENT,
                              GL_RENDERBUFFER,
                              renderBuf.GetId());
}