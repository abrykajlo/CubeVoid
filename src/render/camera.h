/* Copyright (C) 2017, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/

#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

using glm::mat4;
using glm::vec3;
using glm::quat;

namespace cv {
namespace render {
class Camera
{
  public:
    Camera(float fovy,
           float aspectRatio,
           float zNear,
           float zFar);
    ~Camera();

    mat4 View();
    mat4 Projection();

    void SetEye(vec3& eye);
    void SetOrientation(quat& orientation);

  private:
    vec3 m_eye = vec3(0.f, 0.f, 1.f);
    quat m_orientation = glm::quat_cast(mat4(1.f));

    float m_fovy;
    float m_aspect;
    float m_zNear;
    float m_zFar;
};
}
}