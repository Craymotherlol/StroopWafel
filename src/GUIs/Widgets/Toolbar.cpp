#include "GUIs/Widgets/Toolbar.h"

void ToolbarWidget(ToolModes &curtool)
{
     ImGuiStyle &style = ImGui::GetStyle();
     ImGuiIO &io = ImGui::GetIO();

     std::vector<std::string> buttonlabels = {
          ICON_FA_ARROW_POINTER, // SELECT
          ICON_FA_BROOM, // DRAW
          ICON_FA_ERASER // ERASE
     };

     for (int i = 0; i < buttonlabels.size(); i++) {
          bool selected = (curtool == static_cast<ToolModes>(i));

          if (selected) {
               ImGui::PushStyleColor(ImGuiCol_Button, style.Colors[ImGuiCol_ButtonHovered]);
          }

          ImGui::PushFont(fontIcons, 20.0f);
          ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(0.7f, 0.5f));
          if (ImGui::Button(buttonlabels[i].c_str(), ImVec2(30.0f, 30.0f))) {
               curtool = static_cast<ToolModes>(i);

               switch (curtool) {
                    case ToolModes::SELECT:
                    break;
                    case ToolModes::DRAW:
                    break;
                    case ToolModes::ERASE:
                    break;
               }
          }
          ImGui::PopStyleVar();
          ImGui::PopFont();

          if (selected) {
               ImGui::PopStyleColor();
          }

          if (i < buttonlabels.size()) {
               ImGui::SameLine();
          }  
     }
};