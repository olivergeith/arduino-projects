/*
 * Nasa.cpp
 *
 *  Created on: 11.02.2016
 *      Author: Oliver
 */

#include "Nasa.h"

Nasa::Nasa(Adafruit_NeoPixel strip) {
	this->strip = strip;
	animating = false;
	animationStep = 0;
}

Nasa::~Nasa() {
	// TODO Auto-generated destructor stub
}

void Nasa::init() {
	animationStep = 0;
}

void Nasa::drawLauflicht(int millies) {
	ms = millies;
	if (ms % 50 == 0) {
		animationStep++;
		if (animationStep == strip.numPixels())
			animationStep = 0;
		for (int i = 0; i < strip.numPixels(); i++) {
			if (i == animationStep || i == animationStep + 1) {
				strip.setPixelColor(i, getColorBlue(255));
			} else {
				strip.setPixelColor(i, 0, 0, 0);
			}
		}
	}
	strip.show();
}

void Nasa::drawEinblenden(int millies) {
	int steps = 20;
	ms = millies;
	if (ms % 50 == 0) {
		animationStep++;
		if (animationStep == 30)
			animationStep = 0;
		for (int i = 0; i < strip.numPixels(); i++) {
			if (animationStep < steps) {
				strip.setPixelColor(i, getColorBlue(animationStep * 255 / steps));
			}
		}
	}
	strip.show();
}

void Nasa::drawEinblendenRedBlue(int millies) {
	int steps = 20;
	ms = millies;
	if (ms % 50 == 0) {
		animationStep++;
		if (animationStep == 30)
			animationStep = 0;
		for (int i = 0; i < strip.numPixels(); i++) {
			if (animationStep < steps) {
				strip.setPixelColor(i, getColorRedToBlue(animationStep * 255 / steps));
			}
		}
	}
	strip.show();
}

void Nasa::drawBlitzeNasa(int millies) {
	ms = millies;
	if (ms % 10 == 0) {
		animationStep++;
		if (animationStep == 12)
			animationStep = 0;
		for (int i = 0; i < strip.numPixels(); i++) {
			if (animationStep < strip.numPixels()) {
				strip.setPixelColor(i, getColorOrangeBlue(animationStep * 255 / strip.numPixels(), i));
			}
		}
	}
	strip.show();
}

void Nasa::drawBlitzeWilliams(int millies) {
	ms = millies;
	if (ms % 10 == 0) {
		animationStep++;
		if (animationStep == 12)
			animationStep = 0;
		for (int i = 0; i < strip.numPixels(); i++) {
			if (animationStep < strip.numPixels()) {
				strip.setPixelColor(i, getColorOrange(animationStep * 255 / strip.numPixels()));
			}
		}
	}
	strip.show();
}

uint32_t Nasa::getColorBlue(int brightness) {
	int b = brightness;
	int r = 0; //255 - brightness;
	return strip.Color(r, 0, b);
}

uint32_t Nasa::getColorRedToBlue(int brightness) {
	int b = brightness;
	int r = 255 - brightness;
	return strip.Color(r, 0, b);
}

uint32_t Nasa::getColorOrangeBlue(int brightness, int index) {
	if (index >= 4 && index <= 15) {
		return strip.Color(brightness, brightness * 1 / 3, 0);
	}
	return strip.Color(0, 0, brightness);
}

uint32_t Nasa::getColorOrange(int brightness) {
	return strip.Color(brightness, brightness * 1 / 3, 0);
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Nasa::Wheel(byte WheelPos) {
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
