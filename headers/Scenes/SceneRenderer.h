#ifndef STROOPWA_SCENE_RENDERER_H
#define STROOPWA_SCENE_RENDERER_H

#include "window.h"
#include "Objects/Wafel.h"

class sceneFrameRenderer : public Scene
{
private:
    GLuint screenVAO, screenVBO;

    std::vector<Vertex> verts = {
        // Bottom Left 0
        {{-0.3f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
        // Bottom right 1
        {{0.3f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f, 0.5f}, {1.0f, 0.0f}},

        // Top right 2
        {{0.3f, 0.5f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},

        // Top left 3
        {{-0.3f, 0.5f, 0.0f}, {1.0f, 1.0f, 0.0f, 0.2f}, {0.0f, 1.0f}},
    };

    std::vector<unsigned int> indis = {
        0,1,3,
        1,2,3,
    };

    Shader shader{"res/Shaders/default.vert", "res/Shaders/default.frag"};
    Shader FrameBufferShader{"res/Shaders/fb.vert", "res/Shaders/fb.frag"};

    std::vector<Texture> tex = {
        {SetTextureFromFile("res\\GFX\\testtex.png"), "texture_diffuse"}};

    Mesh mesh{verts, tex, indis};

    std::unique_ptr<WafelObject> CryingMoon = std::make_unique<WafelObject>(mesh, shader);   

public:
    static WafelFrame Renderer;

    sceneFrameRenderer() {};

    void Begin() override;
    void End() override;
    void Update() override;
    void Render() override;
};
#endif