#pragma once

#include <render/vertex.h>

#include <glad/glad.h>

#include <istream>
#include <vector>

namespace cv {
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
MakeCube(Mesh& mesh, float size);
}