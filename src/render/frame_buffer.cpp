#include "frame_buffer.h"

using namespace cv::render;

FrameBuffer::FrameBuffer()
{
    glGenFramebuffers(1, &m_fbo);
}

FrameBuffer::~FrameBuffer()
{
    glDeleteFramebuffers(1, &m_fbo);
}

void
FrameBuffer::AttachTexture(const Texture& tex)
{
    Bind();
    glFramebufferTexture2D(
        GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex.GetId(), 0);
}

void
FrameBuffer::Bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
}