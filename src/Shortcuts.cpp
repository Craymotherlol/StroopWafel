#include "Shortcuts.h"
#include "Window.h"
#include "Globals.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


bool WIREFRAMEMODE = false;


void KeyShortcuts::toggleWireframeMode() {
    WIREFRAMEMODE = !WIREFRAMEMODE;

    if (WIREFRAMEMODE) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}