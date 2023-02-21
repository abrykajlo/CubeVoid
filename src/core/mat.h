/* Copyright (C) 2017, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/

#pragma once

#include <core/vec.h>

#include <cmath>

struct mat2
{
    float m11, m12;
    float m21, m22;
};

struct mat3
{
    float m11, m12, m13;
    float m21, m22, m23;
    float m31, m32, m33;
};

struct mat4
{
    float m11, m12, m13, m14;
    float m21, m22, m23, m24;
    float m31, m32, m33, m34;
    float m41, m42, m43, m44;
};

template<class MatT>
MatT
eye();

mat4 operator*(const mat4& M1, const mat4& M2);

vec3 operator*(const mat3& M, const vec3& v);

mat4
LookAt(vec3 eye, vec3 at, vec3 up);

mat4
Frustum(float left,
        float right,
        float bottom,
        float top,
        float near,
        float far);