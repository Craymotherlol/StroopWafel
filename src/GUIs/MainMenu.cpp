#include "GUIs/MainMenu.h"
#include "GUIManager.h"
#include <memory>

void MainMenuUI::Begin() {
	LoadTextureFromFile("E:\\Projects\\Code\\C++\\StroopWafel\\res\\GFX\\logo.png", &logotex, &logowidth, &logoheight);
};

void MainMenuUI::End() {
	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &logotex);
};

void MainMenuUI::Update(){
};

void MainMenuUI::Render()
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

	std::string text = "Welcome to Stroopwafel!";
	ImVec2 textSize = ImGui::CalcTextSize(text.c_str());

	ImGui::SetCursorPosX((windowSize.x - textSize.x) / 2);
	ImGui::Text(text.c_str());

	ImGui::Image((ImTextureID)logotex, ImVec2(logowidth / 2, logoheight / 2));

	ImGui::SetCursorPosX((windowSize.x - 300) / 2);
	text = "LEVEL EDITOR (CETTALYKE)";

	if (ImGui::Button(text.c_str(), ImVec2(300, 50)))
	{
		guimanager.SetLayout("lvleditor");
	}

	ImGui::End();
};