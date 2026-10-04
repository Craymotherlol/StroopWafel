#ifndef STROOP_WINDOW_H
#define STROOP_WINDOW_H

#include <iostream>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#include <nfd.hpp>
#include <nfd_glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "StroopConfig.h"
#include "Managers.h"

class WindowOptions {
public:
    static ImVec2 windowSize;
    static std::string windowTitle;
    static int vSync;
};

#endif