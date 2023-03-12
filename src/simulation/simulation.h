/* Copyright (C) 2017, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/

#pragma once

#include <engine/clock.h>

namespace cv {
class SimulationManager
{
  public:
    SimulationManager();
    ~SimulationManager();

    int Init();
    int Quit();
    int Update(Clock::DurationT deltaTime);
};
}