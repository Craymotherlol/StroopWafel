#include "../Managers.h"
#include "Helpers/LoadTexture.h"

// If you read this message this language really sucks, hate it. - Cray

class MainMenuUI : public Scene
{
private:
    int logowidth, logoheight;
    unsigned int logotex;
public:
    MainMenuUI() {};

    void Begin() override;
    void End() override;
    void Update() override;
    void Render() override;
};