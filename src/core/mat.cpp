/* Copyright (C) 2017, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/

#include "mat.h"

template<>
mat2
eye()
{
    return { 1, 0, 0, 1 };
}

template<>
mat3
eye()
{
    return { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
}

template<>
mat4
eye()
{
    return { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
}

mat4 operator*(const mat4& M1, const mat4& M2)
{
    return {
        M1.m11 * M2.m11 + M1.m12 * M2.m21 + M1.m13 * M2.m31 + M1.m14 * M2.m41,
        M1.m11 * M2.m12 + M1.m12 * M2.m22 + M1.m13 * M2.m32 + M1.m14 * M2.m42,
        M1.m11 * M2.m13 + M1.m12 * M2.m23 + M1.m13 * M2.m33 + M1.m14 * M2.m43,
        M1.m11 * M2.m14 + M1.m12 * M2.m24 + M1.m13 * M2.m34 + M1.m14 * M2.m44,
        M1.m21 * M2.m11 + M1.m22 * M2.m21 + M1.m23 * M2.m31 + M1.m24 * M2.m41,
        M1.m21 * M2.m12 + M1.m22 * M2.m22 + M1.m23 * M2.m32 + M1.m24 * M2.m42,
        M1.m21 * M2.m13 + M1.m22 * M2.m23 + M1.m23 * M2.m33 + M1.m24 * M2.m43,
        M1.m21 * M2.m14 + M1.m22 * M2.m24 + M1.m23 * M2.m34 + M1.m24 * M2.m44,
        M1.m31 * M2.m11 + M1.m32 * M2.m21 + M1.m33 * M2.m31 + M1.m34 * M2.m41,
        M1.m31 * M2.m12 + M1.m32 * M2.m22 + M1.m33 * M2.m32 + M1.m34 * M2.m42,
        M1.m31 * M2.m13 + M1.m32 * M2.m23 + M1.m33 * M2.m33 + M1.m34 * M2.m43,
        M1.m31 * M2.m14 + M1.m32 * M2.m24 + M1.m33 * M2.m34 + M1.m34 * M2.m44,
        M1.m41 * M2.m11 + M1.m42 * M2.m21 + M1.m43 * M2.m31 + M1.m44 * M2.m41,
        M1.m41 * M2.m12 + M1.m42 * M2.m22 + M1.m43 * M2.m32 + M1.m44 * M2.m42,
        M1.m41 * M2.m13 + M1.m42 * M2.m23 + M1.m43 * M2.m33 + M1.m44 * M2.m43,
        M1.m41 * M2.m14 + M1.m42 * M2.m24 + M1.m43 * M2.m34 + M1.m44 * M2.m44,
    };
}

vec3 operator*(const mat3& M, const vec3& v)
{
    return {
        M.m11 * v.x + M.m12 * v.y + M.m13 * v.z,
        M.m21 * v.x + M.m22 * v.y + M.m23 * v.z,
        M.m31 * v.x + M.m32 * v.y + M.m33 * v.z,
    };
}

mat4
LookAt(vec3 eye, vec3 at, vec3 up)
{
    auto Z = normalize(at - eye);
    auto X = normalize(cross(Z, up));
    auto Y = cross(X, Z);

    return { X.x, X.y, X.z, -dot(X, eye), Y.x, Y.y, Y.z, -dot(Y, eye),
             Z.x, Z.y, Z.z, -dot(Z, eye), 0,   0,   0,   1 };
}

mat4
Frustum(float left, float right, float bottom, float top, float near, float far)
{
    return { 2 * near / (right - left),
             0,
             (right + left) / (right - left),
             0,
             0,
             2 * near / (top - bottom),
             (top + bottom) / (top - bottom),
             0,
             0,
             0,
             (near + far) / (near - far),
             2 * near * far / (near - far),
             0,
             0,
             -1,
             0 };
}