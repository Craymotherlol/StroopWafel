#ifndef STROOP_WINDOW_H
#define STROOP_WINDOW_H

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <nfd.hpp>
#include <nfd_glfw3.h>
#include <string>
//#include "SceneManager.h"
#include "GUIManager.h"

class WindowOptions {
public:
    ImVec2 WINDOWSIZE;
    std::string WINDOWTITLE;
};

#endif