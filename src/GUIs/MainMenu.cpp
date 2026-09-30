#include "GUIs/MainMenu.h"
#include "Managers.h"
#include <memory>

void MainMenuUI::Begin() {
	LoadTextureFromFile("res\\GFX\\logo.png", &logotex, &logowidth, &logoheight);
};

void MainMenuUI::End() {
	glDeleteTextures(1, &logotex);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
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

	//ImGui::SetCursorPosX((windowSize.x - (logowidth / 1.3)) / 2);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, logotex);
	ImVec2 imagesize = ImageKeepRatio(&logotex, 600,400);

	ImGui::SetCursorPosX((windowSize.x - imagesize.x) / 2);

	ImGui::Image((ImTextureID)logotex, imagesize);

	ImGui::SetCursorPosX((windowSize.x - 300) / 2);
	text = "LEVEL EDITOR (CETTALYKE)";

	if (ImGui::Button(text.c_str(), ImVec2(300, 50)))
	{
		guimanager.Set("lvleditor");
		scenemanager.Set("scenerenderer");
	}
	text = "Programming by Craymotherlol (Mehmet Eray Özüduru)";

	textSize = ImGui::CalcTextSize(text.c_str());
	ImGui::SetCursorPosX((windowSize.x - textSize.x) / 2);
	ImGui::Text(text.c_str());

	ImGui::End();
};