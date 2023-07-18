#pragma once

#include "gl.h"

#include "../rect.h"

#include <cstdint>

namespace cv {
namespace render {
namespace gl {
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
struct GLTraits<Texture>
{
    static void gen(GLuint& id) { glGenTextures(1, &id); }
    static void del(const GLuint id) { glDeleteTextures(1, &id); }
    static void bind(const GLuint id) { glBindTexture(GL_TEXTURE_2D, id); }
};
}
}
}