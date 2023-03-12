/* Copyright (C) 2017, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/

#pragma once

#include <glad/glad.h>

#include <string>

namespace cv {
enum ShaderType
{
    VERTEX_SHADER = 0,
    TESS_CONTROL_SHADER = 1,
    TESS_EVALUATION_SHADER = 2,
    GEOMETRY_SHADER = 3,
    FRAGMENT_SHADER = 4,
    COMPUTE_SHADER = 5
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