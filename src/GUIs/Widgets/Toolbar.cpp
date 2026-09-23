#include "GUIs/Widgets/Toolbar.h"

void ToolbarWidget(ToolModes* curtool) {
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoBackground | 
    ImGuiWindowFlags_NoResize | 
    ImGuiWindowFlags_NoMove | 
    ImGuiWindowFlags_NoScrollbar | 
    ImGuiWindowFlags_NoTitleBar;

    std::cout << "AFTER:" << curtool << "\n";

    if (ImGui::Button("Select", ImVec2(40.0f,40.0f))) {
        //*curtool = SELECT;
    };

    ImGui::SameLine();

    if (ImGui::Button("Brush", ImVec2(40.0f,40.0f))) {
        //*curtool = DRAW;
    };

    ImGui::SameLine();

    if (ImGui::Button("Erase", ImVec2(40.0f,40.0f))) {
        //*curtool = ERASE;
    };
};