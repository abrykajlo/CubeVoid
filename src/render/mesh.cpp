/* Copyright (C) 2017, Adam Brykajlo, Inc - All Rights Reserved
** Unauthorized copying of this file, via any medium is strictly prohibited
** Proprietary and confidential
** Written by Adam Brykajlo <adam.brykajlo@gmail.com>, June 2017
*/

#include "mesh.h"

#include <core/math.h>

#include <glm/gtx/rotate_vector.hpp>

#include <algorithm>
#include <istream>

static constexpr int k_cube_faces = 6;
static constexpr int k_indices_per_face = 6;
static constexpr int k_vertices_per_face = 4;

using namespace cv::render;

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

    glVertexAttribPointer(
        0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, v));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
        1, 3, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, n));
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
cv::render::ParseObj(std::basic_istream<char>& is, Mesh& mesh)
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
                indices.push_back(--p);
                indices.push_back(--q);
                indices.push_back(--r);
                break;
        }
    }

    mesh.add_vertices(std::move(vertices));
    mesh.add_indices(std::move(indices));

    return true;
}

void
cv::render::MakeCube(Mesh& mesh)
{
    constexpr int cube_vertices_count = k_cube_faces * k_vertices_per_face;
    const vec3 cube_points[cube_vertices_count] = {
        // right face
        { 0.5f, 0.5f, 0.5f },
        { 0.5f, -0.5f, 0.5f },
        { 0.5f, -0.5f, -0.5f },
        { 0.5f, 0.5f, -0.5f },

        // top face
        { 0.5f, 0.5f, 0.5f },
        { 0.5f, 0.5f, -0.5f },
        { -0.5f, 0.5f, -0.5f },
        { -0.5f, 0.5f, 0.5f },

        // left face
        { -0.5f, -0.5f, -0.5f },
        { -0.5f, -0.5f, 0.5f },
        { -0.5f, 0.5f, 0.5f },
        { -0.5f, 0.5f, -0.5f },

        // bottom face
        { -0.5f, -0.5f, -0.5f },
        { 0.5f, -0.5f, -0.5f },
        { 0.5f, -0.5f, 0.5f },
        { -0.5f, -0.5f, 0.5f },

        // front face
        { 0.5f, 0.5f, 0.5f },
        { -0.5f, 0.5f, 0.5f },
        { -0.5f, -0.5f, 0.5f },
        { 0.5f, -0.5f, 0.5f },

        // back face
        { -0.5f, -0.5f, -0.5f },
        { 0.5f, -0.5f, -0.5f },
        { 0.5f, 0.5f, -0.5f },
        { -0.5f, 0.5f, -0.5f },
    };
    const vec3 cube_normals[k_cube_faces] = {
        // right normal
        { 1, 0, 0 },

        // top normal
        { 0, 1, 0 },

        // left normal
        { -1, 0, 0 },

        // bottom normal
        { 0, -1, 0 },

        // front normal
        { 0, 0, 1 },

        // back normal
        { 0, 0, -1 },
    };

    std::vector<Vertex> vertices;
    vertices.reserve(24);
    for (size_t face = 0; face < k_cube_faces; face++) {
        int base_index = face * k_vertices_per_face;

        vertices.emplace_back(
            Vertex{ cube_points[base_index + 0], cube_normals[face] });
        vertices.emplace_back(
            Vertex{ cube_points[base_index + 1], cube_normals[face] });
        vertices.emplace_back(
            Vertex{ cube_points[base_index + 2], cube_normals[face] });
        vertices.emplace_back(
            Vertex{ cube_points[base_index + 3], cube_normals[face] });
    }

    std::vector<GLuint> indices;
    indices.reserve(36);
    for (size_t face = 0; face < k_cube_faces; face++) {
        GLuint base_index = face * 4;

        // triangle 1
        indices.push_back(base_index + 0);
        indices.push_back(base_index + 1);
        indices.push_back(base_index + 2);

        // triangle 2
        indices.push_back(base_index + 0);
        indices.push_back(base_index + 2);
        indices.push_back(base_index + 3);
    }

    mesh.add_indices(std::move(indices));
    mesh.add_vertices(std::move(vertices));
}

void
cv::render::MakeTorus(Mesh& mesh,
                      float innerRadius,
                      float outerRadius,
                      int latSegs,
                      int longSegs)
{
    const float latSegAngle = 2.f * M_PI / latSegs;
    const float longSegAngle = 2.f * M_PI / longSegs;
    const float centerRadius = (outerRadius + innerRadius) / 2;
    const float crossSectionRadius = (outerRadius - innerRadius) / 2;

    std::vector<Vertex> vertices;
    vertices.reserve(latSegs * longSegs);

    // generate vertices
    float longAngle = 0;
    for (size_t i = 0; i < longSegs; i++) {
        float latAngle = 0;
        vec3 centerPoint(centerRadius * glm::cos(longAngle),
                         0,
                         centerRadius * glm::sin(longAngle));
        for (size_t j = 0; j < latSegs; j++) {
            Vertex v;

            const float r = centerRadius + crossSectionRadius * glm::cos(latAngle);
            v.v.x = r * glm::cos(longAngle);
            v.v.y = crossSectionRadius * glm::sin(latAngle);
            v.v.z = r * glm::sin(longAngle);

            v.n = glm::normalize(v.v - centerPoint);

            vertices.push_back(v);

            latAngle += latSegAngle;
        }
        longAngle += longSegAngle;
    }

    std::vector<GLuint> indices;
    indices.reserve(latSegs * longSegs * 6);

    // generate indices
    for (size_t i = 0; i < longSegs; i++) {
        const int latRing = i * longSegs;
        for (size_t j = 0; j < latSegs; j++) {
            int bottomRight = latRing + j;
            int topRight = latRing + (j + 1) % latSegs;
            int bottomLeft = (bottomRight + latSegs) % vertices.size();
            int topLeft = (topRight + latSegs) % vertices.size();

            indices.push_back(bottomRight);
            indices.push_back(topRight);
            indices.push_back(topLeft);

            indices.push_back(bottomRight);
            indices.push_back(topLeft);
            indices.push_back(bottomLeft);
        }
    }

    mesh.add_vertices(std::move(vertices));
    mesh.add_indices(std::move(indices));
}

void
cv::render::MakeSphere(Mesh& mesh, int latSegs, int longSegs)
{
    const float latSegAngle = M_PI / latSegs;
    const float longSegAngle = 2.f * M_PI / longSegs;

    int numVertices = 2 + (latSegs - 2) * longSegs;
    std::vector<Vertex> vertices;
    vertices.reserve(numVertices);

    // add North Pole
    vec3 point(0, 1, 0);
    vertices.emplace_back(Vertex{ point, point });

    for (size_t i = 0; i < latSegs - 2; i++) {
        point = glm::rotateZ(point, latSegAngle);
        for (size_t j = 0; j < longSegs; j++) {
            vertices.emplace_back(Vertex{ point, point });
            point = glm::rotateY(point, longSegAngle);
        }
    }

    // add South Pole
    point = vec3(0, -1, 0);
    vertices.emplace_back(Vertex{ point, point });

    std::vector<GLuint> indices;
    // add top triangles
    for (size_t i = 1; i <= longSegs; i++) {
        indices.push_back(i % longSegs + 1);
        indices.push_back(0);
        indices.push_back(i);
    }

    // add body
    for (size_t i = 0; i < latSegs - 2; i++) {
        const int firstTopLeft = 1 + i * longSegs;
        for (size_t j = 0; j < longSegs; j++) {
            int topLeft = firstTopLeft + j;
            int topRight = firstTopLeft + (j + 1) % longSegs;
            int bottomLeft = topLeft + longSegs;
            int bottomRight = bottomLeft + 1;

            indices.push_back(topLeft);
            indices.push_back(bottomLeft);
            indices.push_back(bottomRight);

            indices.push_back(topLeft);
            indices.push_back(bottomRight);
            indices.push_back(topRight);
        }
    }

    // add bottom triangles
    int startOfBottom = numVertices - longSegs - 1;
    for (size_t i = 0; i < longSegs; i++) {
        indices.push_back(startOfBottom + i);
        indices.push_back(numVertices - 1);
        indices.push_back(startOfBottom + i + 1);
    }

    // add to mesh
    mesh.add_vertices(std::move(vertices));
    mesh.add_indices(std::move(indices));
}
