#pragma once

#include "drawable.h"

#include <glad/gl.h>
#include <glm/vec3.hpp>

#include <vector>

namespace cv {
namespace render {
class PointSprites : public IDrawable
{
  public:
    PointSprites();
    ~PointSprites();

    int Init();
    int Quit();

    void AddPoints(std::vector<glm::vec3>&& ps);

    int Draw() override;

  private:
    GLuint m_vao;
    GLuint m_vbo;

    std::vector<glm::vec3> m_points;
};
}
}
