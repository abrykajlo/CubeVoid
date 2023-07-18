/* Copyright (C) 2017, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/

#pragma once

#include "camera.h"
#include "context.h"
#include "mesh.h"

#include <engine/clock.h>

#include <entt/entt.hpp>

#include <SDL.h>
#include <memory>

namespace cv {
namespace core {
class Log;
}
namespace render {
namespace gl {
class ShaderProgram;
}

class Context;
class Window;
class RenderManager
{
  public:
    RenderManager(const Window& window, entt::registry& registry);
    ~RenderManager();

    int Init();

    int Render(const engine::Clock::DurationT& deltaTime);

  private:
    int InitShaders();
    Camera GetMainCamera();
    float GetAspectRatio();

    const Window& m_window;
    std::unique_ptr<core::Log> m_log;
    std::unique_ptr<gl::ShaderProgram> m_shaderProgram;
    entt::registry& m_EnTTRegistry;
    engine::Clock::DurationT m_timeSinceLastRender;
};
}
}