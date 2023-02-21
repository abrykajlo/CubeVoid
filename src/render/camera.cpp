/* Copyright (C) 2017, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/

#include "camera.h"

Camera::Camera()
{
    eye = { 0, 1, 1 };
    at = { 0, 0, 0 };
    up = { 0, 1, 0 };

    m_projection = { 0.1f, 0, 0, 0, 0, 0.1f, 0, 0, 0, 0, 0.1f, 0, 0, 0, 0, 1 };
}

Camera::~Camera() {}

mat4
Camera::ViewProjection()
{
    return m_projection * LookAt(eye, at, up);
}
