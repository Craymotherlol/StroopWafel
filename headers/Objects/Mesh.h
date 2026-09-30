#ifndef STROOP_GL_MESH_H
#define STROOP_GL_MESH_H
#include "Window.h"
#include <Objects/Shader.h>
#include <glm/glm.hpp>
#include <vector>

struct Vertex
{
    glm::vec3 position;
    glm::vec4 color;
    glm::vec2 texUV;
};

struct Texture
{
    GLuint id;
    std::string type;
};

class Mesh
{

public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    unsigned int VAO;

    ~Mesh()
    {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);

        for (unsigned int i = 0; i < textures.size(); i++)
        {
            glDeleteTextures(1, &textures[i].id);
        }
    };

    Mesh(const std::vector<Vertex> _verts, const std::vector<Texture> _texs, std::vector<unsigned int> _indis = {})
    {
        this->vertices = _verts;
        if (!_indis.empty())
        {
            this->indices = _indis;
        }
        this->textures = _texs;

        SetupData();
    };

private:
    unsigned int VBO, EBO;

    void SetupData()
    {
        std::cout << "Generating Data:" << &VAO << "\n";
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

        // POSITION
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
        glEnableVertexAttribArray(0);

        // COLOR
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, color));
        glEnableVertexAttribArray(1);

        // TEXTURES
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, texUV));
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);

        std::cout << "Done generating:" << &VAO << "\n";
    }
};
#endif