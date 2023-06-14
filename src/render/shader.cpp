/* Copyright (C) 2017, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/

#include "shader.h"

#include <glad/gl.h>

#include <utility>

using namespace cv::render;

Shader::Shader(ShaderType st)
    : m_shaderType(st)
{
    GLenum glShaderType;
    switch (st) {
        case VERTEX_SHADER:
            glShaderType = GL_VERTEX_SHADER;
            break;
        case TESS_CONTROL_SHADER:
            glShaderType = GL_TESS_CONTROL_SHADER;
            break;
        case TESS_EVALUATION_SHADER:
            glShaderType = GL_TESS_EVALUATION_SHADER;
            break;
        case GEOMETRY_SHADER:
            glShaderType = GL_GEOMETRY_SHADER;
            break;
        case FRAGMENT_SHADER:
            glShaderType = GL_FRAGMENT_SHADER;
            break;
        case COMPUTE_SHADER:
            glShaderType = GL_COMPUTE_SHADER;
            break;
    }
    m_shaderId = glCreateShader(glShaderType);
}

Shader::~Shader()
{
    if (glIsShader(m_shaderId)) {
        glDeleteShader(m_shaderId);
    }
}

void
Shader::SetSource(const char* source)
{
    glShaderSource(m_shaderId, 1, &source, nullptr);
}

int
Shader::Compile()
{
    GLint compileStatus = 0;
    glCompileShader(m_shaderId);

    // check compile status
    glGetShaderiv(m_shaderId, GL_COMPILE_STATUS, &compileStatus);
    if (!compileStatus) {
        return -1;
    }

    return 0;
}

const char*
Shader::GetError()
{
    GLint length = 0;
    glGetShaderiv(m_shaderId, GL_INFO_LOG_LENGTH, &length);
    if (length > 0) {
        m_error.reserve(length);
        glGetShaderInfoLog(m_shaderId, length, nullptr, &m_error[0]);
        return m_error.c_str();
    } else {
        return nullptr;
    }
}