/* Copyright (C) 2017, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/

#pragma once

#include "gl.h"

#include <string>

namespace cv {
namespace render {
namespace gl {
enum ShaderType
{
    VERTEX,
    TESS_CONTROL,
    TESS_EVALUATION,
    GEOMETRY,
    FRAGMENT,
    COMPUTE,
};

GL_ENUM_MAP(ShaderType::VERTEX, GL_VERTEX_SHADER)
GL_ENUM_MAP(ShaderType::TESS_CONTROL, GL_TESS_CONTROL_SHADER)
GL_ENUM_MAP(ShaderType::TESS_EVALUATION, GL_TESS_EVALUATION_SHADER)
GL_ENUM_MAP(ShaderType::GEOMETRY, GL_GEOMETRY_SHADER)
GL_ENUM_MAP(ShaderType::FRAGMENT, GL_FRAGMENT_SHADER)
GL_ENUM_MAP(ShaderType::COMPUTE, GL_COMPUTE_SHADER)

template<ShaderType type>
class Shader : public GLObject<Shader<type>>
{
  public:
    Shader() {}
    ~Shader() {}

    void SetSource(const char* source)
    {
        glShaderSource(m_id, 1, &source, nullptr);
    }

    int Compile()
    {
        GLint compileStatus = 0;
        glCompileShader(m_id);

        // check compile status
        glGetShaderiv(m_id, GL_COMPILE_STATUS, &compileStatus);
        if (!compileStatus) {
            return -1;
        }

        return 0;
    }

    std::string GetError()
    {
        GLint length = 0;
        glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &length);
        if (length > 0) {
            std::string error;
            error.reserve(length);
            glGetShaderInfoLog(m_id, length, nullptr, error.data());
            return error;
        } else {
            return nullptr;
        }
    }
};

template<ShaderType type>
struct GLTraits<Shader<type>>
{
    static void gen(GLuint& id)
    {
        id = glCreateShader(GL_ENUM_CAST(type));
    }
    static void del(const GLuint id) { glDeleteShader(id); }
};
}
}
}