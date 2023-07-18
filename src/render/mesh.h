#pragma once

#include "gl/vertex.h"

#include <glad/gl.h>

#include <istream>
#include <vector>

namespace cv {
namespace render {
class Mesh
{
  public:
    Mesh();
    ~Mesh();

    int Init();
    int Quit();

    int Draw();

    void add_vertices(std::vector<Vertex>&& vs);
    void add_indices(std::vector<GLuint>&& is);

  private:
    std::vector<Vertex> m_vertices;
    std::vector<GLuint> m_indices;

    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_vio;
};

bool
ParseObj(std::basic_istream<char>& is, Mesh& mesh);

void
MakeCube(Mesh& mesh);

void
MakeTorus(Mesh& mesh,
          float innerRadius = 0.5,
          float outerRadius = 1.0,
          int latSegs = 20,
          int longSegs = 20);

void
MakeSphere(Mesh& mesh, int latitudeSegments = 20, int longitudeSegments = 20);
}
}
