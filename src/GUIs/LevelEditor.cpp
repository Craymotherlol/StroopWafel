#include "GUIs/LevelEditor.h"
#include "GUIManager.h"

void LevelEditorUI::Begin()
{
};

void LevelEditorUI::End() {};

void LevelEditorUI::Update() {};

void LevelEditorUI::Render()
{
	bool show = true;
	int width, height;

	GLFWwindow *window = glfwGetCurrentContext();

	glfwGetFramebufferSize(window, &width, &height);

	ImGui::SetNextWindowSize(ImVec2(static_cast<float>(width / 2), static_cast<float>(height - 30)));
	ImGui::SetNextWindowPos(ImVec2(static_cast<float>(width / 2), static_cast<float>(height / 2)), ImGuiCond_Always, ImVec2(0.5, 0.5));

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(40, 20));
	ImGui::Begin("INFO", &show, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);
	ImGui::PopStyleVar();

	ImVec2 windowSize = {ImGui::GetWindowWidth(), ImGui::GetWindowHeight()};

	std::string text = "...";
	ImGui::Text(text.c_str());

	ImGui::End();
};

// if (room == leveleditor)  {
// 	ToolbarUI();
// 	var node_id = ImGui.GetID("Workspace");

//     ImGui.SetNextWindowPos(0,  frameHeight);
//     ImGui.SetNextWindowSize(window_get_width(), window_get_height() - frameHeight);

//     ImGui.PushStyleVar(ImGuiStyleVar.WindowRounding, 0);
//     ImGui.PushStyleVar(ImGuiStyleVar.WindowBorderSize, 0);
//     ImGui.PushStyleVar(ImGuiStyleVar.WindowPadding, 0, 0);

//     var host_flags = ImGuiWindowFlags.NoTitleBar
//         | ImGuiWindowFlags.NoCollapse
//         | ImGuiWindowFlags.NoResize
//         | ImGuiWindowFlags.NoMove
//         | ImGuiWindowFlags.NoBringToFrontOnFocus
//         | ImGuiWindowFlags.NoNavFocus
//         | ImGuiWindowFlags.NoBackground

//     ImGui.Begin("Workspace", undefined, host_flags);
//     ImGui.PopStyleVar(3);

//     ImGui.DockSpace(node_id, 0, 0, ImGuiDockNodeFlags.NoUndocking | ImGuiDockNodeFlags.AutoHideTabBar);
//     ImGui.End();
	
// 		//#region Layers Window
// 	ImGui.Begin("Layers", undefined, window_flags);
// 	ImGui.Text("WIP");
// 	ImGui.End();
	
// 	ImGui.Begin("Toolbar", undefined, window_flags);
// 	ImGui.Text("WIP");
// 	ImGui.End();
	
	
// 	#endregion
// 	//
// 	//#region Assets Window
// 	imgui_preview();
	
// 	ImGui.Begin("Assets", undefined, window_flags );
// 	if (ImGui.BeginTabBar("Assets"))
//     {
// 		if (ImGui.BeginTabItem("Objects"))
// 		{
// 		    ImGui.Text("WIP");
// 		    ImGui.EndTabItem();
// 		}
		
// 		if (ImGui.BeginTabItem("Enemies"))
// 		{
// 		    ImGui.Text("WIP");
// 		    ImGui.EndTabItem();
// 		}
// 		ImGui.EndTabBar();
// 	}	
// 	ImGui.End();
	
// 	ImGui.Begin("Selections", undefined, window_flags );
// 	ImGui.End();
// 	#endregion
	
// 	ImGui.Begin("Properties",  undefined, window_flags);
// 	ImGui.TextColored("WIP", c_yellow);
// 	ImGui.End();
	

// 	if (!leveleditor_built)
// 	{
// 		ImGui.DockBuilderRemoveNode(node_id);
// 	   ImGui.DockBuilderAddNode(node_id);
		
// 	    //ImGui.DockBuilderSetNodePos(node_id,0,frameHeight);
		
// 	    //ImGui.DockBuilderSetNodeSize(node_id,window_get_width(),window_get_height());
		
// 		var dock1 = ImGui.DockBuilderSplitNode(node_id, ImGuiDir.Left, 0.1);
// 		node_id = dock1[2];
// 		dock1 = dock1[0];
		
		
// 		var dock2 = ImGui.DockBuilderSplitNode(node_id, ImGuiDir.Right, 0.25);
// 		node_id = dock2[2];
// 		dock2 = dock2[0];
		
// 		//ImGui.DockBuilderAddNode(dock2, ImGuiDockNodeFlags.AutoHideTabBar);
		
// 		var dock3 = ImGui.DockBuilderSplitNode(dock2, ImGuiDir.Right, 0.1);
// 		dock2 = dock3[2];
// 		dock3 = dock3[0];
		
// 		//ASSETS DOCK
// 		var dock4 = ImGui.DockBuilderSplitNode(dock2, ImGuiDir.Down, 0.2);
// 		dock2 = dock4[2];
// 		dock4 = dock4[0];
		
// 		var dock5 = ImGui.DockBuilderSplitNode(dock4, ImGuiDir.Left, 0.1);
// 		dock4 = dock5[2];
// 		dock5 = dock5[0];
// 		///
		
// 		var dock6 = ImGui.DockBuilderSplitNode(dock1, ImGuiDir.Up, 0.07);
// 		dock1 = dock6[2];
// 		dock6 = dock6[0];
		
		
// 		ImGui.DockBuilderDockWindow("Layers", dock1);
// 		//ImGui.DockBuilderAddNode(dock2, ImGuiDockNodeFlags.AutoHideTabBar)
// 		ImGui.DockBuilderDockWindow("Viewport", dock2);
// 		ImGui.DockBuilderDockWindow("Properties", dock3);
// 		ImGui.DockBuilderDockWindow("Assets", dock4);
// 		ImGui.DockBuilderDockWindow("Selections", dock5);
// 	   	ImGui.DockBuilderDockWindow("Toolbar", dock6);
			
// 	    ImGui.DockBuilderFinish(node_id);
	
// 	    leveleditor_built = true;
// 	}
	
// }