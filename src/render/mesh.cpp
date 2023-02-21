/* Copyright (C) 2017, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/

#include "mesh.h"

#include <algorithm>
#include <istream>

Mesh::Mesh() {}

Mesh::~Mesh() {}

int
Mesh::Init()
{
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 sizeof(Vertex) * m_vertices.size(),
                 &m_vertices[0],
                 GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
        1, 3, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)sizeof(vec3));
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &m_vio);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vio);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 sizeof(GLuint) * m_indices.size(),
                 &m_indices[0],
                 GL_STATIC_DRAW);

    return 0;
}

int
Mesh::Quit()
{
    glBindVertexArray(m_vao);
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_vio);
    glDeleteVertexArrays(1, &m_vao);
    return 0;
}

int
Mesh::Draw()
{
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr);
    return 0;
}

void
Mesh::add_vertices(std::vector<Vertex>&& v)
{
    m_vertices = v;
}

void
Mesh::add_indices(std::vector<GLuint>&& is)
{
    m_indices = is;
}

bool
Parse(std::basic_istream<char>& is, Mesh& mesh)
{
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    int numVertices = 0;
    int numIndices = 0;
    char nextChar;
    // check how many v and f there are naively
    while (!is.eof()) {
        nextChar = is.get();
        if (nextChar == 'v') {
            numVertices++;
        } else if (nextChar == 'f') {
            numIndices += 3;
        }
    }
    is.clear();
    is.seekg(0);
    vertices.reserve(numVertices);
    indices.reserve(numIndices);
    Vertex vert;
    while (!is.eof()) {
        nextChar = is.get();
        switch (nextChar) {
            case 'v':
                vert.n = { 0, 0, 0 };
                is >> vert.v.x;
                is >> vert.v.y;
                is >> vert.v.z;
                vertices.push_back(vert);
                break;
            case 'f':
                GLuint p, q, r;
                is >> p;
                is >> q;
                is >> r;
                p--;
                q--;
                r--;
                indices.push_back(p);
                indices.push_back(q);
                indices.push_back(r);
                break;
        }
    }

    mesh.add_vertices(std::move(vertices));
    mesh.add_indices(std::move(indices));

    return true;
}
