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

void AnimatorCircle::setHasAnimation(boolean hasIt) {
	this->hasAnimation = hasIt;
}

boolean AnimatorCircle::isHasAnimation(void) {
	return this->hasAnimation;
}

void AnimatorCircle::draw(int newVal) {
	if (oldVal != newVal) {
		oldVal = newVal;
		animating = true;
		animationStep = 1;
	}
	if (hasAnimation == false) {
		animating = false;
	}
	// wenn im Animationg Mode
	if (animating) {
		int index = newVal + animationStep;
//		uint32_t col = Wheel(random(255));
		uint32_t col = Wheel(((animationStep * 256 / strip.numPixels())));
		setPixel(index, col);
		// animation fortsetzen ?
		animationStep++;
		if (animationStep == strip.numPixels()) {
			animating = false;
		}
	} else {
		// sonst ganz normal den Zeiger setzen
		setPixel(newVal, color);
	}
}

void AnimatorCircle::setPixel(int index, uint32_t color) {
	if (index >= strip.numPixels()) {
		index = index - strip.numPixels();
	}
	strip.setPixelColor(index, color);
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

