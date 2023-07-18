/* Copyright (C) 2017, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/

#pragma once

#include "gl.h"
#include "shader.h"

#include <array>
#include <memory>
#include <string>

namespace cv {
namespace render {
namespace gl {
class ShaderProgram : public GLObject<ShaderProgram>
{
  public:
    ShaderProgram();
    ~ShaderProgram();
    
    template<ShaderType type>
    void AttachShader(const Shader<type>& shader) const
    {
        glAttachShader(m_id, shader.GetId());
    }
    
    int Link() const;
    void Use() const;
    std::string GetError() const;
};

template<>
struct GLTraits<ShaderProgram>
{
    static void gen(GLuint& id) { id = glCreateProgram(); }
    static void del(const GLuint id) { glDeleteProgram(id); }
};
}
}
}