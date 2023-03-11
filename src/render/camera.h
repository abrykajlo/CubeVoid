/* Copyright (C) 2017, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/

#pragma once

#include <glm/glm.hpp>

using glm::mat4;
using glm::vec3;

class Camera
{
  public:
    Camera();
    ~Camera();

    mat4 View();
    mat4 Projection();


  private:
    vec3 m_eye;
    vec3 m_up;
    vec3 m_at;

    mat4 m_projection;
};