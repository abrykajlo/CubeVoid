/* Copyright (C) 2017, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/

#pragma once

#include <glad/glad.h>

#include <string>

namespace cv {
namespace render {
enum ShaderType
{
    VERTEX_SHADER,
    TESS_CONTROL_SHADER,
    TESS_EVALUATION_SHADER,
    GEOMETRY_SHADER,
    FRAGMENT_SHADER,
    COMPUTE_SHADER,
    COUNT,
};

class Shader
{
  public:
    friend class ShaderProgram;

    Shader(ShaderType st);
    ~Shader();

    void SetSource(const char* source);
    int Compile();
    const char* GetError();

  private:
    ShaderType m_shaderType;
    GLuint m_shaderId;
    std::string m_error;
};
}
}