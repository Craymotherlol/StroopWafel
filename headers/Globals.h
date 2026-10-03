#ifndef STROOP_GLOBALS_H
#define STROOP_GLOBALS_H

#include "window.h"
#include "lib/IconsFontAwesome7.h"

enum class ToolModes : int
{
    SELECT,
    DRAW,
    ERASE
};


extern GLfloat DeltaTime;
extern GLuint FallbackTexture;

#endif