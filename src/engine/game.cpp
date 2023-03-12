#include "game.h"

#include <render/render.h>
#include <simulation/simulation.h>

#include <SDL.h>

using namespace cv;

Game::Game() {}

Game::~Game() {}

int
Game::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return -1;
    }

    m_renderManager = std::make_unique<RenderManager>();
    if (m_renderManager->Init() < 0) {
        return -1;
    }

    m_simulationManager = std::make_unique<SimulationManager>();
    if (m_simulationManager->Init() < 0) {
        return -1;
    }

    return 0;
}

int
Game::Quit()
{
    SDL_Quit();

    if (m_simulationManager->Quit() < 0) {
        return -1;
    }

    if (m_renderManager->Quit() < 0) {
        return -1;
    }
    return 0;
}

int
Game::Run()
{
    bool quit = false;
    while (!quit) {
        m_clock.Start();
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
        m_simulationManager->Update(m_clock.GetTimeDelta());
        m_renderManager->Render();
        m_clock.Stop();
    }
    return 0;
}
