/* Copyright (C) 2017, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/

#pragma once

#include <engine/clock.h>
#include <render/camera.h>
#include <render/mesh.h>

#include <entt/entt.hpp>
#include <SDL.h>

#include <memory>

namespace cv {
namespace core {
class Log;
}
namespace render {
class ShaderProgram;
class RenderManager
{
  public:
    RenderManager(entt::registry& registry);
    ~RenderManager();

    int Init();
    int Quit();

    int Render(const engine::Clock::DurationT& deltaTime);

  private:
    int InitShaders();
    Camera GetMainCamera();
    float GetAspectRatio();

    SDL_Window* m_window = nullptr;
    SDL_GLContext m_context = nullptr;
    std::unique_ptr<core::Log> m_log;
    std::unique_ptr<ShaderProgram> m_shaderProgram;
    entt::registry& m_EnTTRegistry;
    engine::Clock::DurationT m_timeSinceLastRender;
};
}
}