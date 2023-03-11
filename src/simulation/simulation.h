/* Copyright (C) 2017, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/

#pragma once

class SimulationManager
{
  public:
    SimulationManager();
    ~SimulationManager();

    static SimulationManager& GetInstance();
    int Run();

  private:
    bool m_done = false;
};

int
BigInit();
int
BigQuit();