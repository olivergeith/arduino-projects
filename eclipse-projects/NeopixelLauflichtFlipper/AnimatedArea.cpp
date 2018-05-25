/*
 * AnimatedArea.cpp
 *
 *  Created on: 11.02.2016
 *      Author: Oliver
 */

#include "AnimatedArea.h"

AnimatedArea::AnimatedArea(Adafruit_NeoPixel strip) {
	this->strip = strip;
	animating = false;
	animationStep = 0;
}

AnimatedArea::~AnimatedArea() {
	// TODO Auto-generated destructor stub
}

void AnimatedArea::draw() {
	animationStep++;

	for (int i = 0; i < strip.numPixels(); i++) {
		if (i < animationStep) {
			strip.setPixelColor(i, 200, 0, 0);
		} else {
			strip.setPixelColor(i, 0, 0, 0);
		}
	}

	if (animationStep == strip.numPixels()) {
		animationStep = 0;
	}

}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t AnimatedArea::Wheel(byte WheelPos) {
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
