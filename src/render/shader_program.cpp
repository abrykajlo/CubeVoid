/* Copyright (C) 2017, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/

#include "shader_program.h"

#include <iostream>

using namespace cv::render;

ShaderProgram::ShaderProgram()
    : m_shaders{ nullptr }
{
    m_programId = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
    if (glIsProgram(m_programId)) {
        glDeleteProgram(m_programId);
    }
}

int
ShaderProgram::AttachShader(const Shader& shader)
{
    // if (m_shaders[shader.m_shaderType].get() != nullptr) {
    //     glDetachShader(m_programId, m_shaders[shader.m_shaderType]->m_shaderId);
    // }
    glAttachShader(m_programId, shader.m_shaderId);

    //m_shaders[shader.m_shaderType].reset(&shader);
    return 0;
}

int
ShaderProgram::Link()
{
    GLint linkStatus = 0;
    glLinkProgram(m_programId);

    // check link status
    glGetProgramiv(m_programId, GL_LINK_STATUS, &linkStatus);
    if (!linkStatus) {
        return -1;
    }
    return 0;
}

void
ShaderProgram::Use()
{
    glUseProgram(m_programId);
}

const char*
ShaderProgram::GetError()
{
    GLint length = 0;
    glGetProgramiv(m_programId, GL_INFO_LOG_LENGTH, &length);
    m_error.reserve(length);
    if (length > 0) {
        glGetProgramInfoLog(m_programId, length, nullptr, &m_error[0]);
        return m_error.c_str();
    } else {
        return nullptr;
    }
}
