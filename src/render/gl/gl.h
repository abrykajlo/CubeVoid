#pragma once

#include <glad/gl.h>

namespace cv {
namespace render {
namespace gl {
template<class E, E e>
static const GLenum k_glEnum = static_assert(false, "Not implemented.");

#define GL_ENUM_MAP(ENUM, GL) \
    template<> \
    static const GLenum k_glEnum<decltype(ENUM), ENUM> = GL;

#define GL_ENUM_CAST(ENUM) k_glEnum<decltype(ENUM), ENUM>
    
template<class T>
struct GLTraits
{};

template<class T>
class GLObject
{
    using GLTraits = GLTraits<T>;

  public:
    GLObject() { Gen(); }

    virtual ~GLObject() { Delete(); }

    void Gen() { GLTraits::gen(m_id); }
    void Bind() const { GLTraits::bind(m_id); }
    void Delete()
    {
        if (m_id) {
            GLTraits::del(m_id);
        }
        m_id = 0;
    }

    GLuint GetId() const { return m_id; }

  protected:
    GLuint m_id = 0;
};
}
}
}