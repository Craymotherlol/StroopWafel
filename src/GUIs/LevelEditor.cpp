#include "GUIs/LevelEditor.h"
#include "GUIs/Widgets/Toolbar.h"
#include "GUIs/Menubar.h"
#include "Scenes/SceneRenderer.h"

void LevelEditorUI::Begin()
{
    leveleditor_built = false;
    // CURRENT_TOOL = &modes;
};

void LevelEditorUI::End() {
};

void LevelEditorUI::Update() {
};

void LevelEditorUI::Render()
{
    ImGui::ShowStyleEditor();
    MenuBarUI();
    ImGuiID node_id = ImGui::GetID("Workspace");
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
    GLFWwindow *window = glfwGetCurrentContext();
    int tmpw, tmph;

    glfwGetWindowSize(window, &tmpw, &tmph);

    ImGui::SetNextWindowPos(ImVec2(0, ImGui::GetFrameHeight()));
    ImGui::SetNextWindowSize(ImVec2(tmpw, tmph - ImGui::GetFrameHeight()));

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

    ImGui::Begin("Workspace", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoBackground);

    ImGui::DockSpace(node_id, ImVec2(0, 0), ImGuiDockNodeFlags_NoUndocking | ImGuiDockNodeFlags_AutoHideTabBar | ImGuiDockNodeFlags_PassthruCentralNode);
    ImGui::End();

    if (!leveleditor_built)
    {
        ImGui::DockBuilderRemoveNode(node_id);
        ImGui::DockBuilderAddNode(node_id);

        ImGuiID dock1 = ImGui::DockBuilderSplitNode(node_id, ImGuiDir_Left, 0.1f, NULL, &node_id);

        ImGuiID dock2 = ImGui::DockBuilderSplitNode(node_id, ImGuiDir_Right, 0.25f, NULL, &node_id);
        ImGui::DockBuilderGetNode(dock2)->LocalFlags = ImGuiDockNodeFlags_NoCloseButton | ImGuiDockNodeFlags_NoUndocking | ImGuiDockNodeFlags_NoTabBar;

        ImGuiID dock3 = ImGui::DockBuilderSplitNode(dock2, ImGuiDir_Right, 0.1f, NULL, &dock2);

        ImGuiID dock4 = ImGui::DockBuilderSplitNode(dock2, ImGuiDir_Down, 0.2f, NULL, &dock2);

        ImGuiID dock5 = ImGui::DockBuilderSplitNode(dock4, ImGuiDir_Left, 0.1f, NULL, &dock4);

        // ImGuiID dock6 = ImGui::DockBuilderSplitNode(dock1, ImGuiDir_Up, 0.07f, NULL, &dock1);

        ImGui::DockBuilderDockWindow("Layers", dock1);
        ImGui::DockBuilderDockWindow("Viewport", dock2);
        ImGui::DockBuilderDockWindow("Properties", dock3);
        ImGui::DockBuilderDockWindow("Assets", dock4);
        ImGui::DockBuilderDockWindow("Selections", dock5);
        // ImGui::DockBuilderDockWindow("Toolbar", dock6);

        ImGui::DockBuilderFinish(node_id);

        leveleditor_built = true;
    }
    // std::cout << "BEFORE:" << CURRENT_TOOL << "\n";


    ImGui::Begin("Layers", NULL, window_flags);
    ImGui::Text("WIP");
    ImGui::End();

    ImGui::Begin("Assets");

    // if (ImGui::BeginTabBar("Assets"))
    //{
    //     if (ImGui::BeginTabItem("Objects"))
    //     {
    //         ImGui::Text("WIP");
    //         ImGui::EndTabItem();
    //     }

    //    if (ImGui::BeginTabItem("Enemies"))
    //    {
    //        ImGui::Text("WIP");
    //        ImGui::EndTabItem();
    //    }
    //    ImGui::EndTabBar();
    //}
    ImGui::End();

    ImGui::Begin("Viewport", NULL, ImGuiWindowFlags_NoDecoration);
    ImVec2 viewportcurpos = ImGui::GetCursorScreenPos();
    ImVec2 viewportsize = ImGui::GetWindowSize();

    ImGui::Image((ImTextureID)(intptr_t)sceneFrameRenderer::Renderer.TEXTURE, viewportsize);
    ImGui::End();

    ImGui::SetNextWindowPos(ImVec2(viewportcurpos.x+5.0f, viewportcurpos.y+5.0f), 0 , ImVec2(0,0));
    ImGui::Begin("Toolbar", NULL, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoTitleBar);
    ToolbarWidget(CURRENT_TOOL);
    ImGui::End();

    ImGui::Begin("Selections", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);
    ImGui::End();

    ImGui::Begin("Properties", NULL, window_flags);
    ImGui::TextColored(ImVec4(0, 255, 255, 255), "WIP");
    ImGui::End();

    ImGui::PopStyleVar(3);
}
