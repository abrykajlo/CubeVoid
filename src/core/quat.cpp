#include "quat.h"

#include <cmath>

quat operator*(const quat& q1, const quat& q2)
{
    return { q1.j * q2.k - q1.k * q2.j + q1.i * q2.real + q1.real * q2.i,
             q1.k * q2.i - q1.i * q2.k + q1.j * q2.real + q1.real * q2.j,
             q1.i * q2.j - q1.j * q2.i + q1.k * q2.real + q1.real * q2.k,
             q1.real * q2.real - q1.i * q2.i - q1.j * q2.j - q1.k * q2.k };
}

quat
quat_rotation(float theta, float ux, float uy, float uz)
{
    vec3 axis = { ux, uy, uz };
    return quat_rotation(theta, axis);
}

quat
quat_rotation(float theta, vec3& axis)
{
    float halfSin = sinf(theta / 2);
    float halfCos = cosf(theta / 2);
    auto axisNorm = normalize(axis);
    return { axisNorm.x * halfSin,
             axisNorm.y * halfSin,
             axisNorm.z * halfSin,
             halfCos };
}

quat::quat(float i, float j, float k, float real)
    : i(i)
    , j(j)
    , k(k)
    , real(real)
{}

quat::quat(const vec3& v)
    : i(v.x)
    , j(v.y)
    , k(v.z)
    , real(0)
{}

quat::quat(const vec4& v)
    : i(v.x)
    , j(v.y)
    , k(v.z)
    , real(v.w)
{}

vec4
quat::ToVec4()
{
    return { i, j, k, real };
}

vec3
quat::ToVec3()
{
    return { i, j, k };
}

quat
quat::Conjugate()
{
    return { -i, -j, -k, real };
}

quat
quat::Inverse()
{
    float normSquared = i * i + j * j + k * k + real * real;
    return {
        -i / normSquared, -j / normSquared, -k / normSquared, real / normSquared
    };
}
