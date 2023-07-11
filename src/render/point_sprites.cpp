#include "point_sprites.h"

using namespace cv::render;

PointSprites::PointSprites() {}

PointSprites::~PointSprites() {}

int
PointSprites::Init()
{
    // generate vertex array object
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    // generate vertex buffer object
    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(glm::vec3) * m_points.size(),
                 m_points.data(),
                 GL_STATIC_DRAW);
    return 0;
}

int
PointSprites::Quit()
{
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    return 0;
}

void
PointSprites::AddPoints(std::vector<glm::vec3>&& ps)
{
    m_points = ps;
}

int
PointSprites::Draw()
{
    glBindVertexArray(m_vao);
    glDrawArrays(GL_POINTS, 0, m_points.size());
    return 0;
}
