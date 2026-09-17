#pragma once
#include <iostream>
#include <memory>
#include "Window.h"



class Scene {
    public:
        virtual ~Scene() {std::cout << "Removed Scene" << "\n";};
        virtual void Begin();
        virtual void End();
        virtual void Update();
        virtual void Render();
};

class SceneManager {
    private:
         std::unique_ptr<Scene> CURRENT_SCENE;
    public:
        void SwitchTo(std::unique_ptr<Scene> NextScene) {
            if (CURRENT_SCENE) {
                CURRENT_SCENE->End();
            }

            CURRENT_SCENE = std::move(NextScene);

            if (CURRENT_SCENE) {
                CURRENT_SCENE->Begin();
            }
        };

        void Update() {
            CURRENT_SCENE->Update();
        }

        void Render() {
            CURRENT_SCENE->Render();
        }
};  