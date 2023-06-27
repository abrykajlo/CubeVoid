#pragma once

#include "gl_object.h"

#include "rect.h"

#include <glad/gl.h>

namespace cv {
namespace render {
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
struct GLObjectTraits<RenderBuffer>
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
