#pragma once

namespace cv {
namespace render {
class IDrawable
{
  public:
    virtual ~IDrawable(){};
    virtual int Draw() = 0;
};
}
}