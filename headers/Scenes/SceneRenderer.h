#ifndef STROOPWA_SCENE_RENDERER_H
#define STROOPWA_SCENE_RENDERER_H

#include "window.h"
#include "Objects/Wafel.h"

class sceneFrameRenderer : public Scene
{
private:
    GLuint screenVAO, screenVBO;

public:
    static WafelFrame Renderer;
    
    sceneFrameRenderer() {};

    void Begin() override;
    void End() override;
    void Update() override;
    void Render() override;
};
#endif