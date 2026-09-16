#include "globals.h"
#include <iostream>
#include <string>
#include "SceneManager.h"


//FramesGUI::FramesGUI(GLFWwindow *w)
//{
//	this->window = w;
//};

void FramesGUI::MainMenu(GLFWwindow *window)
{
	bool show = true;
	int width, height;

	glfwGetFramebufferSize(window, &width, &height);

	ImGui::SetNextWindowSize(ImVec2(width / 2, height - 30));
	ImGui::SetNextWindowPos(ImVec2(width / 2, height / 2), ImGuiCond_Always, ImVec2(0.5, 0.5));

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(40, 20));
	ImGui::Begin("INFO", &show, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);
	ImGui::PopStyleVar();

	ImVec2 windowSize = {ImGui::GetWindowWidth(), ImGui::GetWindowHeight()};

	std::string text = "Welcome to Stroopwafel!";
	ImVec2 textSize = ImGui::CalcTextSize(text.c_str());

	ImGui::SetCursorPosX((windowSize.x - textSize.x) / 2);
	ImGui::Text(text.c_str());

	ImGui::SetCursorPosX((windowSize.x - 300) / 2);
	text = "LEVEL EDITOR (CETTALYKE)";

	if (ImGui::Button(text.c_str(), ImVec2(300, 50))) {
		CURRENT_FRAME = CLYKE_LVLEDITOR;
	}

	ImGui::End();
};


// ImGui.PushStyleVar(ImGuiStyleVar.WindowPadding, 40, 20)

// ImGui.Begin("INFO", true, ImGuiWindowFlags.NoCollapse | ImGuiWindowFlags.NoResize | ImGuiWindowFlags.NoMove | ImGuiWindowFlags.NoTitleBar)

// ImGui.PopStyleColor();
// ImGui.PopStyleVar();
// var windowW = ImGui.GetWindowWidth();
// var windowH = ImGui.GetWindowHeight();

// ImGui.CenterText("Welcome to Stroopwafel!")

// ImGui.SetCursorPosX((windowW - 600) / 2)
// ImGui.ImageKeepRatio(sp_logo, 0, c_white, 1, 600)
// ImGui.Separator();

// ImGui.SetCursorPosX((windowW - 300) / 2)
// if (ImGui.Button("LEVEL EDITOR", 300, 50)) {
// 	room_goto(leveleditor)
// }
// ImGui.SameLine();
//
// if (ImGui.Button("FILE BROWSER", 300, 50)) {
// 	room_goto(leveleditor)
// }

// ImGui.CenterText("Programmed by Craymotherlol")
// ImGui.PopStyleVar();

// ImGui.End();
