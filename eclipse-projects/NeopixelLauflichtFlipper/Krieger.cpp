/*
 * Krieger.cpp
 *
 *  Created on: 11.02.2016
 *      Author: Oliver
 */

#include "Krieger.h"

Krieger::Krieger(Adafruit_NeoPixel strip) {
	this->strip = strip;
	animating = false;
	animationStep = 0;
}

Krieger::~Krieger() {
	// TODO Auto-generated destructor stub
}

void Krieger::draw() {
	animationStep++;

	for (int i = 0; i < strip.numPixels(); i++) {
		if (i < animationStep) {
			strip.setPixelColor(i, getColorForIndex(i));
		} else {
			strip.setPixelColor(i, 0, 0, 0);
		}
	}

	if (animationStep == 50) {
		animationStep = 0;
	}

}

uint32_t Krieger::getColorForIndex(int index) {
	if (index == 10 || index == 9) {
		return strip.Color(0, 0, 255);
	}

	return strip.Color(200, 0, 0); // rot
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Krieger::Wheel(byte WheelPos) {
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
