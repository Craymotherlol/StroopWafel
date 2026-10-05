#ifndef STROOPWA_SCENE_RENDERER_H
#define STROOPWA_SCENE_RENDERER_H

#include "window.h"
#include "Objects/Wafel.h"
#include "Objects/Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class sceneFrameRenderer : public Scene
{
private:
    GLuint screenVAO, screenVBO;

    std::vector<Vertex> verts = {
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},   
        {{0.5f,  -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
        {{0.5f,   0.5f, -0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
        {{0.5f,   0.5f, -0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
        {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
        {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},

        {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
        {{ 0.5f, -0.5f,  0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
        {{ 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
        {{ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
        {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
        {{-0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},

        {{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
        {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
        {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
        {{-0.5f, -0.5f,  0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
        {{-0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},

        {{ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
        {{ 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
        {{ 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
        {{ 0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
        {{ 0.5f, -0.5f,  0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
        {{ 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},

        {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
        {{ 0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
        {{ 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
        {{ 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
        {{-0.5f, -0.5f,  0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
        {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},

        {{-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
        {{ 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
        {{ 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
        {{ 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
        {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
        {{-0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}}

    };

    //std::vector<unsigned int> indis = {
    //    0,1,3,
    //    1,2,3,
    //};

    Shader shader{"res/Shaders/default.vert", "res/Shaders/default.frag"};
    Shader FrameBufferShader{"res/Shaders/fb.vert", "res/Shaders/fb.frag"};

    std::vector<Texture> tex = {
        {SetTextureFromFile("res\\GFX\\testtex.png"), "texture_diffuse"}};

    Mesh mesh{verts, tex};

    std::unique_ptr<WafelObject> CryingMoon = std::make_unique<WafelObject>(mesh, shader);   

    glm::mat4 projection        = glm::mat4(1.0f);
    glm::mat4 view              = glm::mat4(1.0f);

    float lastX = WindowOptions::windowSize.x / 2.0f;
    float lastY = WindowOptions::windowSize.y / 2.0f;

    bool firstMouse = true;

public:
    static WafelFrame Renderer;
    static Camera camera;

    sceneFrameRenderer() {};

    void Begin() override;
    void End() override;
    void Update() override;
    void Render() override;

    void ProcessInput(GLFWwindow* window);
};
#endif