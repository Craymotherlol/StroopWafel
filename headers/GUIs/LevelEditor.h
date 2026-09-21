#include "../GUIManager.h"

class LevelEditorUI : public GUILayout
{
private:
    bool leveleditor_built;
    GLFWwindow *window;
public:
    LevelEditorUI() {};

    void Begin() override;
    void End() override;
    void Update() override;
    void Render() override;
};