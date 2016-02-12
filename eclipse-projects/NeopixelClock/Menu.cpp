/*
 * Menu.cpp
 *
 *  Created on: 11.02.2016
 *      Author: Oliver
 */

#include "Menu.h"

Menu::Menu(int maxMode) {
	mode = 0;
	this->MAXMODE = maxMode;
}

Menu::~Menu() {
}

void Menu::increment() {
	mode++;
	if (mode > MAXMODE) {
		mode = 0;
	}
}

int Menu::getCurrentModeInt() {
	return mode;
}

char* Menu::getCurrentMode() {

	switch (mode) {
	default:
	case 0:
		return "";
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
		return "Animate Seconds";
	}
}
