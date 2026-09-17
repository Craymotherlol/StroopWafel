#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <toml++/toml.hpp>
#include "Window.h"

enum Layouts : int {
    MAINMENU,
    CLYKE_LVLEDIT,
    CLYKE_RESVIEW
};

class GuiLayout {
public:
    //FramesGUI(GLFWwindow* w);
    static void MainMenu();

//private:
//    GLFWwindow* window;
};

extern int CURRENT_GUILAYOUT;
