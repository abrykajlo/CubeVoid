/* Copyright (C) 2017, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/

#pragma once

#include <engine/clock.h>

#include <entt/entt.hpp>

#include <memory>

namespace cv {
namespace sim {
class SimulationManager
{
  public:
    SimulationManager(entt::registry& registry);
    ~SimulationManager();

    int Init();
    int Quit();
    int Update(const engine::Clock::DurationT& deltaTime);

  private:
    entt::registry& m_EnTTRegistry;
};
}
}