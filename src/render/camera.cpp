/* Copyright (C) 2017, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/

#include "camera.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

using namespace cv;

Camera::Camera()
    : m_eye(1, 2, 2)
    , m_at(0, 0, 0)
    , m_up(0, 1, 0)
    , m_projection(glm::perspective(glm::radians(45.0f), 640.f/480, 0.1f, 100.f))
{}

Camera::~Camera() {}

mat4
Camera::View()
{
    return glm::lookAt(m_eye, m_at, m_up);
}

mat4
Camera::Projection()
{
    return m_projection;
}