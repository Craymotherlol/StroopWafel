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
extern const std::string RESOURCE_PATH;
extern const std::string SHADERS_PATH;
extern const std::string FONTS_PATH;

extern GLuint FallbackTexture;
extern ImFont* fontIcons;

#endif