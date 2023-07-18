#pragma once

#include "gl.h"

#include "../rect.h"

namespace cv {
namespace render {
namespace gl {
class RenderBuffer : public GLObject<RenderBuffer>
{
  public:
    RenderBuffer();
    RenderBuffer(const Rect& rect);
    virtual ~RenderBuffer();

    const Rect& GetRect();
    void SetRect(const Rect& rect);

  private:
    void UpdateStorage();

    Rect m_rect;
};

template<>
struct GLTraits<RenderBuffer>
{
    static void gen(GLuint& id) { glGenRenderbuffers(1, &id); }
    static void del(const GLuint id) { glDeleteRenderbuffers(1, &id); }
    static void bind(const GLuint id)
    {
        glBindRenderbuffer(GL_RENDERBUFFER, id);
    }
};
}
}
}
