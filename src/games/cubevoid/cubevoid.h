#pragma once

#include <engine/game.h>

class CubeVoidGame : public cv::engine::Game
{
  public:
    virtual int Init() override;
    virtual int Quit() override;
};