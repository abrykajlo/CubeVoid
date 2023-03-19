#pragma once

#include <render/mesh.h>

namespace cv {
namespace render {
namespace component {
struct MainCamera
{
    float fovy;
    float zNear;
    float zFar;
};

struct Light
{
    vec3 La;
    vec3 Ld;
    vec3 Ls;
};

struct Material
{
    vec3 Ka;
    vec3 Kd;
    vec3 Ks;
};

struct Mesh
{
    render::Mesh mesh;
};

struct Scale
{
    float scale;
};
}
}
}