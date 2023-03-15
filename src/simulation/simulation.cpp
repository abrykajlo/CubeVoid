/* Copyright (C) 2017, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/

#include "simulation.h"

#include <entt/entt.hpp>

#include <memory>

using namespace cv::sim;

SimulationManager::SimulationManager(entt::registry& registry)
    : m_EnTTRegistry(registry)
{}

SimulationManager::~SimulationManager() {}

int
SimulationManager::Init()
{
    return 0;
}

int
SimulationManager::Quit()
{
    return 0;
}

int
SimulationManager::Update(const engine::Clock::DurationT& deltaTime)
{
    return 0;
}
