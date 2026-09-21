#include "../GUIManager.h"
#include "Helpers/LoadTexture.h"

// If you read this message this language really sucks, hate it. - Cray

class MainMenuUI : public GUILayout
{
private:
    int logowidth, logoheight;
    unsigned int logotex;
    
    GUIManager& guimanager;
public:
    MainMenuUI(GUIManager& guimgr) : guimanager(guimgr) {};

    void Begin() override;
    void End() override;
    void Update() override;
    void Render() override;
};