#ifndef STROOP_WAFELOBJECT_H
#define STROOP_WAFELOBJECT_H

#include "Shader.h"
#include "Mesh.h"
#include "../Helpers/LoadTexture.h"
#include "../window.h"

// Yeah cute name :PPP

// Stores mesh and shader into one object.

class WafelObject {
    private:
        std::shared_ptr<Mesh> mesh;
        std::shared_ptr<Shader> shader;
    public:
        glm::mat4 transform = glm::mat4(1.0f);

        ~WafelObject() {
            mesh.reset();
            shader.reset();
        }
        
        WafelObject(Mesh& _mesh, Shader& _shader) {
            mesh = std::make_shared<Mesh>(_mesh);
            shader = std::make_shared<Shader>(_shader);
        }

        std::shared_ptr<Shader> GetShader() {
            return shader;
        };

        void Draw()
        {
            unsigned int diffuseNr = 1;
            unsigned int specularNr = 1;
            for (unsigned int i = 0; i < mesh->textures.size(); i++)
            {
                glActiveTexture(GL_TEXTURE0 + i);
                std::string number;
                std::string name = mesh->textures[i].type;
                if (name == "texture_diffuse") {
                    number = std::to_string(diffuseNr++);
                } else if (name == "texture_specular") {
                    number = std::to_string(specularNr++);
                }
            
                glUniform1i(glGetUniformLocation(shader->ID, (name + number).c_str()), i);

                if (mesh->textures[i].id != 0) {
                    glBindTexture(GL_TEXTURE_2D, mesh->textures[i].id);
                } else {
                    glBindTexture(GL_TEXTURE_2D, FallbackTexture);
                }
            }

            glBindVertexArray(mesh->VAO);
            if (!mesh->indices.empty()) {
                glDrawElements(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, 0);
            } else {
                glDrawArrays(GL_TRIANGLES, 0, mesh->vertices.size());
            }
            
            glActiveTexture(GL_TEXTURE0);
            glBindVertexArray(0);
        };
};

#endif