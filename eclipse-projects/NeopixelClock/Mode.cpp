/*
 * Mode.cpp
 *
 *  Created on: 11.02.2016
 *      Author: Oliver
 */

#include "Mode.h"

Mode::Mode() {
	mode = 0;
}

Mode::~Mode() {
}

void Mode::increment() {
	mode++;
	if (mode > MAXMODE) {
		mode = 0;
	}
}

int Mode::getCurrentModeInt() {
	return mode;
}

char* Mode::getCurrentMode() {
	switch (mode) {
	default:
	case 0:
		return "";
	case 1:
		return "Set Minute";
	case 2:
		return "Set Hour";
	case 3:
		return "Set Hour";
	case 4:
		return "Set Day";
	case 5:
		return "Set Year";
	}
}
