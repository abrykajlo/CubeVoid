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
    using GenT = GLObjectTraits<T>;

  public:
    GLObject() { GenT::gen(m_id); }

    virtual ~GLObject() { GenT::del(m_id); }

    void Bind() const { GenT::bind(m_id); }

    GLuint GetId() const { return m_id; }

  protected:
    GLuint m_id = 0;
};
}
}
