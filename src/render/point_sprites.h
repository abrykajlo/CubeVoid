#pragma once

#include "drawable.h"

namespace cv {
namespace render {
class PointSprites : public IDrawable
{
  public:
    PointSprites();
    ~PointSprites();

    int Draw() override;
};
}
}
