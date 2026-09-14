// How many "rooms" the application can switch to
enum FRAMES {
	MENU,
	CLYKE_LVLEDITOR
};

extern int CURRENT_FRAME; // Responsible for changing one room to the next (ex: House's have multiple rooms with different purposes)