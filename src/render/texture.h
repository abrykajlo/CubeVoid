#pragma once

#include "gl_object.h"

#include "rect.h"

#include <glad/gl.h>

#include <cstdint>

namespace cv {
namespace render {
class Texture : public GLObject<Texture>
{
  public:
    Texture();
    Texture(const Rect& rect);
    virtual ~Texture();

    const Rect& GetRect();
    void SetRect(const Rect& rect);

  private:
    void UpdateStorage();

    Rect m_rect;
};

template<>
struct GLObjectTraits<Texture>
{
    static void gen(GLuint& id) { glGenTextures(1, &id); }
    static void del(const GLuint id) { glDeleteTextures(1, &id); }
    static void bind(const GLuint id) { glBindTexture(GL_TEXTURE_2D, id); }
};
}
}