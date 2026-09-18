#pragma once
#include <toml++/toml.hpp>
#include <memory>
#include <unordered_map>
#include <string>
#include "Window.h"

class GUILayout
{
public:
    virtual ~GUILayout() = default;
    virtual void Begin() {};
    virtual void End() {};
    virtual void Update() {};
    virtual void Render() {};
};


class GUIManager {
private:
    std::unordered_map<std::string, std::unique_ptr<GUILayout>> layouts;
    GUILayout* currentLayout = nullptr;

public:

    void AddLayout(const std::string& name, std::unique_ptr<GUILayout> layout) {
        layouts[name] = std::move(layout);
    }

    void SetLayout(const std::string& name) {
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