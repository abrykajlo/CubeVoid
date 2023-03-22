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
    glm::vec3 eye(2, 2, 1);
    glm::vec3 at(0, 0, 0);
    entt::handle camHandle(m_EnTTRegistry, m_EnTTRegistry.create());
    camHandle.emplace<cv::render::component::MainCamera>(
        glm::radians(45.f), 0.1f, 100.f);
    camHandle.emplace<cv::sim::component::Position>(eye);

    camHandle.emplace<cv::sim::component::Rotation>(
        glm::quatLookAt(glm::normalize(at - eye), glm::vec3(0, 1, 0)));

    // setup torus
    entt::handle torus(m_EnTTRegistry, m_EnTTRegistry.create());

    component::Material material;
    material.Ka = vec3(0.3, 0.0, 0.0);
    material.Kd = vec3(1.0, 0.0, 0.0);
    material.Ks = vec3(0.8, 0.8, 0.8);
    torus.emplace<component::Material>(material);

    cv::render::Mesh mesh;
    cv::render::MakeTorus(mesh, 0.3f, 1.f, 50, 100);
    mesh.Init();
    torus.emplace<component::Mesh>(mesh);

    // setup lighting
    entt::handle lightEntity(m_EnTTRegistry, m_EnTTRegistry.create());

    component::Light light;
    light.La = vec3(0.4);
    light.Ld = vec3(0.8);
    light.Ls = vec3(0.8);

    lightEntity.emplace<component::Light>(light);
    lightEntity.emplace<component::Position>(vec3(1, 1, 1));

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