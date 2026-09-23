#ifndef STROOP_GUI_LEVELEDITOR_H
#define STROOP_GUI_LEVELEDITOR_H

#include "GUIs/Menubar.h"
#include "../GUIManager.h"
#include "GUIs/Widgets/Toolbar.h"

class LevelEditorUI : public GUILayout
{
private:
    bool leveleditor_built;
    GLFWwindow *window;
    //ToolModes modes;

public:
   // ToolModes *CURRENT_TOOL;

    LevelEditorUI() {};

    void Begin() override;
    void End() override;
    void Update() override;
    void Render() override;
};
#endif