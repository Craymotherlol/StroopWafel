#ifndef STROOP_MANAGERS_H
#define STROOP_MANAGERS_H

#include <toml++/toml.hpp>
#include <memory>
#include <unordered_map>
#include <string>
#include "Window.h"

// Both managers do the exact same thing to switch between gui layouts and scenes.

class Scene
{
public:
    virtual ~Scene() = default;
    virtual void Begin() {};
    virtual void End() {};
    virtual void Update() {};
    virtual void Render() {};
};


class SceneManager {
private:
    std::unordered_map<std::string, std::unique_ptr<Scene>> scenes;
    Scene* currentScene = nullptr;

public:
     std::string id; // Easier for bool checks I don't have anything else in mind /shrug

    void Add(const std::string& name, std::unique_ptr<Scene> scene) {
        scenes[name] = std::move(scene);
    }

    void Set(const std::string& name) {
        auto it = scenes.find(name);
        if (it == scenes.end()) return;

        id = name;

        if (currentScene) currentScene->End();
        currentScene = it->second.get();
        currentScene->Begin();
    }

    void Update() {
        if (currentScene) currentScene->Update();
    }

    void Render() {
        if (currentScene) currentScene->Render();
    }
};

class GUIManager {
private:
    std::unordered_map<std::string, std::unique_ptr<Scene>> layouts;
    Scene* currentLayout = nullptr;

public:

    void Add(const std::string& name, std::unique_ptr<Scene> layout) {
        layouts[name] = std::move(layout);
    }

    void Set(const std::string& name) {
        auto it = layouts.find(name);
        if (it == layouts.end()) return;

        if (currentLayout) currentLayout->End();
        currentLayout = it->second.get();
        currentLayout->Begin();
    }

    void Update() {
        if (currentLayout) currentLayout->Update();
    }

    void Render() {
        if (currentLayout) currentLayout->Render();
    }
};

extern GUIManager guimanager;
extern SceneManager scenemanager;

#endif