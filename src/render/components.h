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

struct Material
{
    vec3 kd;
    vec3 ks;
    vec3 ka;
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