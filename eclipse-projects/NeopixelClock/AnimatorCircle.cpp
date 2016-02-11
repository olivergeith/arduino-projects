/*
 * AnimatorCircle.cpp
 *
 *  Created on: 11.02.2016
 *      Author: Oliver
 */

#include "AnimatorCircle.h"

AnimatorCircle::AnimatorCircle(Adafruit_NeoPixel strip, uint32_t color,
		boolean hasAnimation) {
	this->hasAnimation = hasAnimation;
	this->strip = strip;
	this->color = color;
	oldVal = 0;
	animating = false;
	animationStep = 0;
}

AnimatorCircle::~AnimatorCircle() {
	// TODO Auto-generated destructor stub
}

void AnimatorCircle::draw(int newVal) {
	if (oldVal != newVal) {
		oldVal = newVal;
		animating = true;
	}
	if (hasAnimation == false) {
		animating = false;
	}
	if (animating) {
		int index = newVal + animationStep;
		if (index >= strip.numPixels()) {
			index = index - strip.numPixels();
		}
		uint32_t col = Wheel(((animationStep * 256 / strip.numPixels())));
		strip.setPixelColor(index, col);
		animationStep++;
		if (animationStep == strip.numPixels()) {
			animationStep = 0;
			animating = false;
		}
	} else {
		strip.setPixelColor(newVal, color);
	}
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t AnimatorCircle::Wheel(byte WheelPos) {
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

