#include "render_buffer.h"

using namespace cv::render::gl;

RenderBuffer::RenderBuffer()
    : RenderBuffer({ 0, 0 })
{
}

RenderBuffer::RenderBuffer(const Rect& rect)
    : m_rect(rect)
{
    UpdateStorage();
}

RenderBuffer::~RenderBuffer() {}

const cv::render::Rect&
RenderBuffer::GetRect()
{
    return m_rect;
}

void
RenderBuffer::SetRect(const Rect& rect)
{
    if (m_rect != rect) {
        m_rect = rect;
        Delete();
        Gen();
        UpdateStorage();
    }
}

void
RenderBuffer::UpdateStorage()
{
    Bind();
    glRenderbufferStorage(
        GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_rect.x, m_rect.y);
}
