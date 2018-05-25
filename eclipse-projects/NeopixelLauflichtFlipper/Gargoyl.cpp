/*
 * Gargoyl.cpp
 *
 *  Created on: 11.02.2016
 *      Author: Oliver
 */

#include "Gargoyl.h"

Gargoyl::Gargoyl(Adafruit_NeoPixel strip) {
	this->strip = strip;
	animating = false;
	animationStep = 0;
}

Gargoyl::~Gargoyl() {
	// TODO Auto-generated destructor stub
}

void Gargoyl::draw() {
	animationStep++;

	for (int i = 0; i <= 1; i++) {
		strip.setPixelColor(i, Wheel(animationStep));
	}

	if (animationStep == 255) {
		animationStep = 0;
	}

}

uint32_t Gargoyl::getColorForIndex(int index) {

	return strip.Color(0, 0, 200); // rot
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Gargoyl::Wheel(byte WheelPos) {
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
