/* Copyright (C) 2017, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/

#pragma once

#include "shader.h"

#include <array>
#include <memory>

namespace cv {
namespace render {
class ShaderProgram
{
  public:
    ShaderProgram();
    ~ShaderProgram();
    
    GLuint GetId();
    int AttachShader(const Shader& shader);
    int Link();
    void Use();
    const char* GetError();

  private:
    std::array<std::unique_ptr<const Shader>, ShaderType::COUNT> m_shaders;

    GLuint m_programId;
    std::string m_error;
};
}
}