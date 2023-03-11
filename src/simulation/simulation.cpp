/* Copyright (C) 2017, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/

#include <render/render.h>
#include <simulation/simulation.h>

#include <SDL.h>

#include <memory>

SimulationManager::SimulationManager() {}

SimulationManager::~SimulationManager() {}

SimulationManager&
SimulationManager::GetInstance()
{
    static std::unique_ptr<SimulationManager> s_simulationManager = nullptr;
    if (s_simulationManager == nullptr) {
        s_simulationManager = std::make_unique<SimulationManager>();
    }
    return *s_simulationManager.get();
}

int
SimulationManager::Run()
{
    auto& renderManager = RenderManager::GetInstance();
    while (!m_done) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                m_done = true;
            }
        }
        renderManager.Render();
    }

    return 0;
}

int
BigInit()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return -1;
    }

    if (RenderManager::GetInstance().Init() < 0) {
        return -1;
    }

    return 0;
}

int
BigQuit()
{
    SDL_Quit();

    if (RenderManager::GetInstance().Quit() < 0) {
        return -1;
    }

    return 0;
}
