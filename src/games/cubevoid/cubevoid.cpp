#include "cubevoid.h"

#include <render/components.h>
#include <simulation/components.h>

#include <glm/gtc/quaternion.hpp>

namespace component {
using namespace cv::render::component;
using namespace cv::sim::component;
}

int
CubeVoidGame::Init()
{
    int result = Game::Init();
    if (result < 0) {
        return result;
    }

    // setup camera
    glm::vec3 eye(-2, 2, 1);
    glm::vec3 at(0, 0, 0);
    entt::handle camHandle(m_EnTTRegistry, m_EnTTRegistry.create());
    camHandle.emplace<cv::render::component::MainCamera>(
        glm::radians(45.f), 0.1f, 100.f);
    camHandle.emplace<cv::sim::component::Position>(eye);

    camHandle.emplace<cv::sim::component::Rotation>(
        glm::quatLookAt(glm::normalize(at - eye), glm::vec3(0, 1, 0)));

    // setup sphere
    entt::handle cube(m_EnTTRegistry, m_EnTTRegistry.create());

    component::Material material;
    material.kd = vec3(1.0, 0.0, 0.0);
    cube.emplace<component::Material>(material);

    cv::render::Mesh mesh;
    cv::render::MakeTorus(mesh);
    mesh.Init();
    cube.emplace<component::Mesh>(mesh);

    return 0;
}

int
CubeVoidGame::Quit()
{
    int result = Game::Quit();
    if (result < 0) {
        return result;
    }

    for (auto entity : m_EnTTRegistry.view<component::Mesh>()) {
        auto& mesh = m_EnTTRegistry.get<component::Mesh>(entity);
        mesh.mesh.Quit();
    }
}