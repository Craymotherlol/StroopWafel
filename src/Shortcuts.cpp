#include "Shortcuts.h"
#include "Window.h"

bool WIREFRAMEMODE = false;

void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_F1 && action == GLFW_PRESS) {
        KeyShortcuts::toggleWireframeMode();
    }
}

void KeyShortcuts::toggleWireframeMode() {
    WIREFRAMEMODE = !WIREFRAMEMODE;

    if (WIREFRAMEMODE) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}