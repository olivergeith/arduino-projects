/*
 * Menu.cpp
 *
 *  Created on: 11.02.2016
 *      Author: Oliver
 */

#include "Menu.h"

Menu::Menu() {
	mode = 0;
}

Menu::~Menu() {
}

void Menu::increment() {
	mode++;
	if (mode > MAXMODE) {
		mode = 0;
	}
}

void Menu::decrement() {
	mode--;
	if (mode < 0) {
		mode = MAXMODE;
	}
}

int Menu::getMaxMode(void) {
	return MAXMODE;
}

int Menu::getCurrentModeInt() {
	return mode;
}

char* Menu::getCurrentMode() {

	switch (mode) {
	default:
	case 0:
		return "Push red for Menu...";
	case 1:
		return "Set Minute";
	case 2:
		return "Set Hour";
	case 3:
		return "Set Day";
	case 4:
		return "Set Month";
	case 5:
		return "Set Year";
	case 6:
		return "Animate Hours";
	case 7:
		return "Animate Minutes";
	case 8:
		return "Animate Seconds";
	case 9:
		return "Color Hours";
	case 10:
		return "Color Minutes";
	case 11:
		return "Color Seconds";
	}
}
