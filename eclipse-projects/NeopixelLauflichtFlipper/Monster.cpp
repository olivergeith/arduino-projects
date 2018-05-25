/*
 * Monster.cpp
 *
 *  Created on: 11.02.2016
 *      Author: Oliver
 */

#include "Monster.h"

Monster::Monster(Adafruit_NeoPixel strip) {
	this->strip = strip;
	animating = false;
	animationStep = 0;
}

Monster::~Monster() {
	// TODO Auto-generated destructor stub
}

void Monster::draw() {
	animationStep++;

	for (int i = 0; i <= 10; i++) {
		if (i < animationStep) {
			strip.setPixelColor(10 - i, getColorForIndex(10 - i));
		} else {
			strip.setPixelColor(10 - i, 0, 0, 0);
		}
	}

	for (int i = 0; i <= 10; i++) {
		if (i < animationStep) {
			strip.setPixelColor(29 - i, getColorForIndex(29 - i));
		} else {
			strip.setPixelColor(29 - i, 0, 0, 0);
		}
	}

	for (int i = 0; i <= 7; i++) {
		if (i < animationStep) {
			strip.setPixelColor(47 - i, getColorForIndex(47 - i));
		} else {
			strip.setPixelColor(47 - i, 0, 0, 0);
		}
	}

	for (int i = 0; i <= 7; i++) {
		if (i < animationStep) {
			strip.setPixelColor(11 + i, getColorForIndex(11 + i));
		} else {
			strip.setPixelColor(11 + i, 0, 0, 0);
		}
	}

	for (int i = 0; i <= 9; i++) {
		if (i < animationStep) {
			strip.setPixelColor(30 + i, getColorForIndex(30 + i));
		} else {
			strip.setPixelColor(30 + i, 0, 0, 0);
		}
	}
	for (int i = 0; i <= 11; i++) {
		if (i < animationStep) {
			strip.setPixelColor(48 + i, getColorForIndex(48 + i));
		} else {
			strip.setPixelColor(48 + i, 0, 0, 0);
		}
	}

	if (animationStep == 150) {
		animationStep = 0;
	}

}

uint32_t Monster::getColorForIndex(int index) {
	if (index <= 5) {
		return strip.Color(200, 0, 200); // rot
	}
	if (index >= 55) {
		return strip.Color(200, 0, 200); // rot
	}

	return strip.Color(0, 64, 200); // rot
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Monster::Wheel(byte WheelPos) {
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
