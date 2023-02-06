/* Copyright (C) 2017, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/

#include "camera.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

Camera::Camera()
    : eye(0, 1, 1)
    , at(0, 0, 0)
    , up(0, 1, 0)
    , m_projection(glm::frustum(-5.f, 5.f, -5.f, 5.f, 0.f, 10.f))
{}

Camera::~Camera() {}

mat4
Camera::ViewProjection()
{
    return m_projection * glm::lookAt(eye, at, up);
}
