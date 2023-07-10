/* Copyright (C) 2023, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, March 2023
*/

#pragma once

#include "clock.h"

#include <render/context.h>
#include <render/window.h>

#include <entt/entt.hpp>

#include <memory>

namespace cv {
namespace render {
class RenderManager;
}
namespace sim {
class SimulationManager;
}

namespace engine {
class Game
{
  public:
    Game();
    virtual ~Game();

    virtual int Init();
    virtual int Quit();
    virtual int Run();

  protected:
    entt::registry m_EnTTRegistry;

  private:
    Clock m_clock;
    render::Window m_window;
    std::unique_ptr<render::Context> m_context;
    std::unique_ptr<render::RenderManager> m_renderManager;
    std::unique_ptr<sim::SimulationManager> m_simulationManager;
};
}
}