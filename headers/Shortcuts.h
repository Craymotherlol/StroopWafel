#ifndef STROOP_KEYSHORTCUTS_H
#define STROOP_KEYSHORTCUTS_H

#include "Window.h"

extern bool WIREFRAMEMODE;

void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

class KeyShortcuts {
    public:
        static void toggleWireframeMode();
};


#endif