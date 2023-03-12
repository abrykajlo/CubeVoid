/* Copyright (C) 2023, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, March 2023
*/

#pragma once

#include <engine/clock.h>

#include <memory>

class SDL_Window;

namespace cv {
class RenderManager;
class SimulationManager;

class Game
{
  public:
    virtual int Init();
    virtual int Quit();
    virtual int Run();

  protected:
    Game();
    virtual ~Game();

  private:
    SDL_Window* m_window;

    Clock m_clock;
    std::unique_ptr<RenderManager> m_renderManager;
    std::unique_ptr<SimulationManager> m_simulationManager;
};
}