#include "vec.h"

vec3
operator/(const vec3& v, float x)
{
    return { v.x / x, v.y / x, v.z / x };
}

vec3
normalize(const vec3& v)
{
    return v / sqrt(dot(v, v));
}

float
dot(const vec3& v1, const vec3& v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

vec3
cross(const vec3& v1, const vec3& v2)
{
    return { v1.y * v2.z - v1.z * v2.y,
             v1.z * v2.x - v1.x * v2.z,
             v1.x * v2.y - v1.y * v2.x };
}

vec3
operator-(const vec3& v1, const vec3& v2)
{
    return { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
}
