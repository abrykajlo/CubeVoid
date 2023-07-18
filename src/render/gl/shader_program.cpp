/* Copyright (C) 2017, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/

#include "shader_program.h"

#include <iostream>

using namespace cv::render::gl;

ShaderProgram::ShaderProgram() {}

ShaderProgram::~ShaderProgram() {}

int
ShaderProgram::Link() const
{
    GLint linkStatus = 0;
    glLinkProgram(m_id);

    // check link status
    glGetProgramiv(m_id, GL_LINK_STATUS, &linkStatus);
    if (!linkStatus) {
        return -1;
    }
    return 0;
}

void
ShaderProgram::Use() const
{
    glUseProgram(m_id);
}

std::string
ShaderProgram::GetError() const
{
    GLint length = 0;
    glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &length);
    if (length > 0) {
        std::string error;
        error.reserve(length);
        glGetProgramInfoLog(m_id, length, nullptr, error.data());
        return error;
    } else {
        return nullptr;
    }
}
