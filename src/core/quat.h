#pragma once

#include <core/vec.h>

struct quat
{
    float i;
    float j;
    float k;
    float real;

    quat(float i, float j, float k, float real);
    quat(const vec3& v);
    quat(const vec4& v);

    // returns w = real
    vec4 ToVec4();

    // Truncates real value and returns {i,j,k}
    vec3 ToVec3();
    quat Conjugate();
    quat Inverse();
};

quat operator*(const quat& q1, const quat& q2);
quat
quat_rotation(float theta, float ux, float uy, float uz);
quat
quat_rotation(float theta, vec3& axis);
// TODO: add euler angle conversion functions