#ifndef STROOPWAFEL_GLFW_WINDOW_H
#define STROOPWAFEL_GLFW_WINDOW_H

#include <iostream>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

class WindowOptions {
public:
    ImVec2 WINDOWSIZE;
    std::string WINDOWTITLE;
};


#endif