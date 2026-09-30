#ifndef STROOP_GUI_LEVELEDITOR_H
#define STROOP_GUI_LEVELEDITOR_H

#include "../Managers.h"
#include "Globals.h"

class LevelEditorUI : public Scene
{
private:
    bool leveleditor_built;
    GLFWwindow *window;

public:
    // prevent garbage value blaaah
    ToolModes CURRENT_TOOL = ToolModes::SELECT;

    LevelEditorUI() {};

    void Begin() override;
    void End() override;
    void Update() override;
    void Render() override;
};
#endif