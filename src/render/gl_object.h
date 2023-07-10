#pragma once

#include <glad/gl.h>

namespace cv {
namespace render {
template<class T>
struct GLObjectTraits
{};

template<class T>
class GLObject
{
    using GLTraits = GLObjectTraits<T>;

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
