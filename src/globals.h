#ifndef STROOPWAFEL_GLOBAL_VARIABLES_H
#define STROOPWAFEL_GLOBAL_VARIABLES_H
#include "window.h"
#include <string>
#include <vector>

// How many "rooms" the application can switch to
enum FRAMES {
	MENU,
	CLYKE_LVLEDITOR
};

extern const bool DEBUG;
extern int CURRENT_FRAME; // Responsible for changing one room to the next (ex: House's have multiple rooms with different purposes)


#endif