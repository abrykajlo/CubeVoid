#pragma once

#include <glm/ext/quaternion_float.hpp>
#include <glm/vec3.hpp>

namespace cv {
namespace sim {
namespace component {
struct Position
{
    glm::vec3 position;
};

struct Rotation
{
    glm::quat rotation;
};
}
}
}