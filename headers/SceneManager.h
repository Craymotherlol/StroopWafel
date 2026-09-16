#pragma once
#include <toml++/toml.hpp>
#include "window.h"


enum SCENES {
    MAINMENU,
    CLYKE_LVLEDIT,
    CLYKE_RESVIEW
};


class FramesGUI {
public:
    //FramesGUI(GLFWwindow* w);
    static void MainMenu(GLFWwindow* w);

//private:
//    GLFWwindow* window;
};
