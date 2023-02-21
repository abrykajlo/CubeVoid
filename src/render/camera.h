/* Copyright (C) 2017, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/

#pragma once

#include <core/mat.h>
#include <core/vec.h>

class Camera
{
  public:
    Camera();
    ~Camera();

    mat4 ViewProjection();

    vec3 eye;
    vec3 up;
    vec3 at;

  private:
    mat4 m_projection;
};