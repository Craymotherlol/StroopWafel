#ifndef STROOP_GL_MESH_H
#define STROOP_GL_MESH_H
#include "Window.h"
#include "Vertex.h"
#include <vector>

class Mesh {
    private:
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
    public:      
        unsigned int VBO, VAO, EBO;
        ~Mesh() {
            glDeleteVertexArrays(1, &VAO);
            glDeleteBuffers(1, &VBO);
            glDeleteBuffers(1, &EBO);
        };

        Mesh(const std::vector<Vertex> _verts, const std::vector<unsigned int> _indis) : vertices(_verts), indices(_indis) {
            SetupData();
        };
        
        void SetupData() {
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glGenBuffers(1, &EBO);
            
            glBindVertexArray(VAO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);  
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

            // POSITION
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
            glEnableVertexAttribArray(0);
 
            // COLOR
            glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
            glEnableVertexAttribArray(1);
            
            glBindBuffer(GL_ARRAY_BUFFER, 0); 

            glBindVertexArray(0);
        }
};
#endif