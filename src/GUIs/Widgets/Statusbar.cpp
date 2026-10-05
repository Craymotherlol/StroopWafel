#include "GUIs/Widgets/Statusbar.h"
#include "Scenes/SceneRenderer.h"

void StatusbarWidget(float regionY)
{
     ImGuiStyle &style = ImGui::GetStyle();
     Camera& cam = sceneFrameRenderer::camera;

     ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
     ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
     ImGui::PushStyleColor(ImGuiCol_WindowBg, style.Colors[ImGuiCol_MenuBarBg]);

     ImGui::SetNextWindowPos(ImVec2(0,regionY));
     ImGui::SetNextWindowSize(ImVec2(WindowOptions::windowSize.x,0.0f));

     ImGui::Begin("Statusbar", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoMouseInputs | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoDocking);

     ImVec2 barheight = ImGui::GetContentRegionAvail();

     std::string Text = "Mouse Position: (X: %i,Y: %i)";
     ImVec2 textSize = ImGui::CalcTextSize(Text.c_str());


     ImGui::SetCursorPosY((barheight.y - textSize.y) / 2);
     ImGui::Text(Text.c_str(), static_cast<int>(MousePosX), static_cast<int>(MousePosY));
     ImGui::SameLine();

     Text = "Camera: (X: %f Y: %f)";
     textSize = ImGui::CalcTextSize(Text.c_str());
     ImGui::Text(Text.c_str(), cam.Position.x, cam.Position.y);

     ImGui::End();

     ImGui::PopStyleColor(1);
     ImGui::PopStyleVar(2);
}; 