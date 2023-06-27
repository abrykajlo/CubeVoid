#include "render_buffer.h"

using namespace cv::render;

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

const Rect&
cv::render::RenderBuffer::GetRect()
{
    return m_rect;
}

void
cv::render::RenderBuffer::SetRect(const Rect& rect)
{
    bool shouldUpdate = false;
    if (m_rect == rect) {
        shouldUpdate;
    }

    m_rect = rect;

    if (shouldUpdate) {
        UpdateStorage();
    }
}

void
cv::render::RenderBuffer::UpdateStorage()
{
    Bind();
    glRenderbufferStorage(
        GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_rect.x, m_rect.y);
}
