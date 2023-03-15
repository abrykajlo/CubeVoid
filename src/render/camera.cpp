/* Copyright (C) 2017, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/

#include "camera.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include <iostream>

using namespace cv::render;

Camera::Camera(float fovy,
               float aspect,
               float zNear,
               float zFar)
    : m_fovy(fovy)
    , m_aspect(aspect)
    , m_zNear(zNear)
    , m_zFar(zFar)
{}

Camera::~Camera() {}

mat4
Camera::View()
{
    mat4 view(glm::conjugate(m_orientation));
    view = glm::translate(view, -m_eye);
    return view;
}

mat4
Camera::Projection()
{
    return glm::perspective(m_fovy, m_aspect, m_zNear, m_zFar);
}

void
Camera::SetEye(vec3& eye)
{
    m_eye = eye;
}

void
Camera::SetOrientation(quat& orientation)
{
    m_orientation = orientation;
}
