/*
 * Arena.cpp
 *
 *  Created on: 11.02.2016
 *      Author: Oliver
 */

#include "Arena.h"

Arena::Arena(Adafruit_NeoPixel strip) {
	this->strip = strip;
	animating = false;
	animationStep = 0;
}

Arena::~Arena() {
	// TODO Auto-generated destructor stub
}

void Arena::draw() {
	animationStep++;

	for (int i = 0; i < strip.numPixels(); i++) {
		if (i < animationStep) {
			strip.setPixelColor(i, getColorForIndex(i));
		} else if (i >= 74) {
			strip.setPixelColor(i, getColorForIndex(i));
		} else {
			strip.setPixelColor(i, 0, 0, 0);
		}
	}

	if (animationStep == strip.numPixels() * 2) {
		animationStep = 0;
	}

}

uint32_t Arena::getColorForIndex(int index) {
	uint32_t white = strip.Color(230, 230, 230);

	if (index >= 5 && index <= 6) {
		return white;
	}

	if (index >= 30 && index <= 50) {
		return white;
	}
	if (index >= 73) {
		return white;
	}

	return strip.Color(250, 80, 0); // rot
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Arena::Wheel(byte WheelPos) {
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
