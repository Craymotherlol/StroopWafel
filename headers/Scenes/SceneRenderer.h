#ifndef STROOPWA_SCENE_RENDERER_H
#define STROOPWA_SCENE_RENDERER_H

#include "window.h"
#include "Objects/WafelObject.h"

class sceneFrameRenderer : public Scene
{
private:
    GLuint frameBuffer, textureColorBuffer, screenVAO, screenVBO;

public:
    sceneFrameRenderer() {};

    void Begin() override;
    void End() override;
    void Update() override;
    void Render() override;
};
#endif