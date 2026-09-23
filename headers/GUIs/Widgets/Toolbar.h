#ifndef STROOP_GUI_TOOLBAR_WIDGET_H
#define STROOP_GUI_TOOLBAR_WIDGET_H

#include "GUIs/LevelEditor.h"
#include "window.h"

enum class ToolModes
{
    SELECT,
    DRAW,
    ERASE
};


void ToolbarWidget(ToolModes* curtool);

#endif