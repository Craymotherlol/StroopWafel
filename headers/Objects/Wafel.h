#ifndef STROOP_WAFELOBJECT_H
#define STROOP_WAFELOBJECT_H

#include "Shader.h"
#include "Mesh.h"
#include "Globals.h"
#include "../Helpers/LoadTexture.h"
#include "../window.h"

// Yeah cute name :PPP

// Frame buffers
class WafelFrame
{
private:
public:
    unsigned int FBO, TEXTURE, RBO;

    ~WafelFrame() {
        glDeleteRenderbuffers(1, &RBO);
        glDeleteTextures(1, &TEXTURE);
        glDeleteFramebuffers(1, &FBO);
    }
    void createFrameBuffer()
    {
        //Frame Buffer
        glGenFramebuffers(1, &FBO);
        glBindFramebuffer(GL_FRAMEBUFFER, FBO);

        // Texture
        glGenTextures(1, &TEXTURE);
        glBindTexture(GL_TEXTURE_2D, TEXTURE);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WindowOptions::windowSize.x, WindowOptions::windowSize.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, TEXTURE, 0);

        //Render buffer
        glGenRenderbuffers(1, &RBO);
        glBindRenderbuffer(GL_RENDERBUFFER, RBO);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WindowOptions::windowSize.x, WindowOptions::windowSize.y);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    void rescaleFrameBuffer(float WIDTH, float HEIGHT)
    {
        glBindTexture(GL_TEXTURE_2D, TEXTURE);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, TEXTURE, 0);

        glBindRenderbuffer(GL_RENDERBUFFER, RBO);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WIDTH, HEIGHT);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);
    }
};

// Stores meshes, shaders and textures.
class WafelObject
{
private:
    std::shared_ptr<Mesh> mesh;
    std::shared_ptr<Shader> shader;

public:
    glm::mat4 transform = glm::mat4(1.0f);

    ~WafelObject()
    {
        mesh.reset();
        shader.reset();
    }

    WafelObject(Mesh &_mesh, Shader &_shader)
    {
        mesh = std::make_shared<Mesh>(_mesh);
        shader = std::make_shared<Shader>(_shader);
    }

    std::shared_ptr<Shader> GetShader()
    {
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
            if (name == "texture_diffuse")
            {
                number = std::to_string(diffuseNr++);
            }
            else if (name == "texture_specular")
            {
                number = std::to_string(specularNr++);
            }

            glUniform1i(glGetUniformLocation(shader->ID, (name + number).c_str()), i);

            if (mesh->textures[i].id != 0)
            {
                glBindTexture(GL_TEXTURE_2D, mesh->textures[i].id);
            }
            else
            {
                glBindTexture(GL_TEXTURE_2D, FallbackTexture);
            }
        }

        glBindVertexArray(mesh->VAO);
        if (!mesh->indices.empty())
        {
            glDrawElements(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, 0);
        }
        else
        {
            glDrawArrays(GL_TRIANGLES, 0, mesh->vertices.size());
        }

        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(0);
    };
};

#endif