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
