#pragma once

#include "mesh.h"

namespace cv {
namespace render {
namespace component {
struct MainCamera
{
    float fovy;
    float zNear;
    float zFar;
};

struct PBRLight
{
    vec3 L;
};

struct PBRMaterial
{
    float Roughness;
    bool Metal;
    vec3 Color;
};

struct PhongLight
{
    vec3 La;
    vec3 Ld;
    vec3 Ls;
};

struct PhongMaterial
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