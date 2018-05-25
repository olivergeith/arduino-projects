/*
 * Kriegerin.cpp
 *
 *  Created on: 11.02.2016
 *      Author: Oliver
 */

#include "Kriegerin.h"

Kriegerin::Kriegerin(Adafruit_NeoPixel strip) {
	this->strip = strip;
	animating = false;
	animationStep = 0;
}

Kriegerin::~Kriegerin() {
	// TODO Auto-generated destructor stub
}

void Kriegerin::draw() {
	animationStep++;

	for (int i = 0; i <= 9; i++) {
		if (i < animationStep) {
			strip.setPixelColor(9 - i, getColorForIndex(9 - i));
		} else {
			strip.setPixelColor(9 - i, 0, 0, 0);
		}
	}

	if (animationStep == 70) {
		animationStep = 0;
	}

}

uint32_t Kriegerin::getColorForIndex(int index) {
	if (index == 9) {
		return strip.Color(0, 0, 255); // rot
	}

	return strip.Color(200, 64, 0); // rot
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Kriegerin::Wheel(byte WheelPos) {
	WheelPos = 255 - WheelPos;
	if (WheelPos < 85) {
		return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
	}
	if (WheelPos < 170) {
		WheelPos -= 85;
		return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
	}
	WheelPos -= 170;
	return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
