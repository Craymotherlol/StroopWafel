#include "../GUIManager.h"

class LevelEditorUI : public GUILayout
{
public:
    LevelEditorUI() {};

    void Begin() override;
    void End() override;
    void Update() override;
    void Render() override;
};