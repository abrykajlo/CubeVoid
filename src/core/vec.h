#pragma once

#include <cmath>

struct vec2
{
    float x, y;
};

struct vec3
{
    float x, y, z;
};

struct vec4
{
    float x, y, z, w;
};

//-------------------------------------------------------------------
// Operators for vec3
//-------------------------------------------------------------------
vec3
operator/(const vec3& v, float x);

vec3
normalize(const vec3& v);

float
dot(const vec3& v1, const vec3& v2);

vec3
cross(const vec3& v1, const vec3& v2);

vec3
operator-(const vec3& v1, const vec3& v2);