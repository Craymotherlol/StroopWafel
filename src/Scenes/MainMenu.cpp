#include "Scenes/MainMenu.h"
#include "main.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


void MainMenuScene::Begin() {
}

void MainMenuScene::End() {
    CryingMoon.reset();
}

void MainMenuScene::Update() {

}

void MainMenuScene::Render() {

    CryingMoon->transform = glm::rotate(CryingMoon->transform, DeltaTime, glm::vec3(0.0f, 1.0f, 0.0f));

    CryingMoon->GetShader()->Use();
    CryingMoon->GetShader()->setMatrix4("model", glm::value_ptr(CryingMoon->transform));

    CryingMoon->Draw();
}