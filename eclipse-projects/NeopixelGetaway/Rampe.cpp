/*
 * RampeHinten.cpp
 *
 *  Created on: 11.02.2016
 *      Author: Oliver
 */

#include "Rampe.h"

Rampe::Rampe(Adafruit_NeoPixel strip) {
	this->strip = strip;
	init();
}

Rampe::~Rampe() {
	// TODO Auto-generated destructor stub
}

void Rampe::init() {
	animating = true;
	animationStep = 0;
	max = strip.numPixels();
}

void Rampe::drawLauflichtBlau(int millies) {
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

void Rampe::drawLauflichtBlauBuildingUp(int millies) {
	ms = millies;
	if (ms % 10 == 0) {
		animationStep++;
		if (animationStep == max) {
			animationStep = 0;
			max--;
			if (max == 0)
				max = strip.numPixels();
		}
		for (int i = 0; i < max; i++) {
			if (i == animationStep) {
				strip.setPixelColor(i, getColorRed(255));
			} else {
				strip.setPixelColor(i, 0, 0, 0);
			}
		}
		for (int i = max; i < strip.numPixels(); i++) {
			strip.setPixelColor(i, getColorBlue(255));
		}
	}
	strip.show();
}

void Rampe::drawTronLightWhite() {
	animationStep++;
	if (animationStep == strip.numPixels() + 5)
		animationStep = -5;
	for (int i = 0; i < strip.numPixels(); i++) {
		if (i == animationStep)
			strip.setPixelColor(i, getColorWhite(164));
		else if (i == animationStep + 1 || i == animationStep - 1)
			strip.setPixelColor(i, getColorWhite(64));
		else if (i == animationStep + 2 || i == animationStep - 2)
			strip.setPixelColor(i, getColorWhite(64));
		else if (i == animationStep + 3 || i == animationStep - 3)
			strip.setPixelColor(i, getColorWhite(32));
		else if (i == animationStep + 4 || i == animationStep - 4)
			strip.setPixelColor(i, getColorWhite(16));
		else if (i == animationStep + 5 || i == animationStep - 5)
			strip.setPixelColor(i, getColorWhite(8));
		else
			strip.setPixelColor(i, 0, 0, 0);
	}
	strip.show();
}

void Rampe::drawTronLightBackAndForthWhite() {

	if (animating)
		animationStep++;
	else
		animationStep--;

	if (animationStep >= strip.numPixels())
		animating = false;
	if (animationStep <= 0)
		animating = true;

	for (int i = 0; i < strip.numPixels(); i++) {
		if (i == animationStep)
			strip.setPixelColor(i, getColorBlue(164));
		else if (i == animationStep + 1 || i == animationStep - 1)
			strip.setPixelColor(i, getColorBlue(64));
		else if (i == animationStep + 2 || i == animationStep - 2)
			strip.setPixelColor(i, getColorBlue(64));
		else if (i == animationStep + 3 || i == animationStep - 3)
			strip.setPixelColor(i, getColorBlue(32));
		else if (i == animationStep + 4 || i == animationStep - 4)
			strip.setPixelColor(i, getColorBlue(16));
		else if (i == animationStep + 5 || i == animationStep - 5)
			strip.setPixelColor(i, getColorBlue(8));
		else
			strip.setPixelColor(i, 0, 0, 0);
	}
	strip.show();
}

void Rampe::drawTronLightRed() {
	animationStep++;
	if (animationStep == strip.numPixels() + 5)
		animationStep = -5;
	for (int i = 0; i < strip.numPixels(); i++) {
		if (i == animationStep)
			strip.setPixelColor(i, getColorRed(164));
		else if (i == animationStep + 1 || i == animationStep - 1)
			strip.setPixelColor(i, getColorRed(64));
		else if (i == animationStep + 2 || i == animationStep - 2)
			strip.setPixelColor(i, getColorRed(64));
		else if (i == animationStep + 3 || i == animationStep - 3)
			strip.setPixelColor(i, getColorRed(32));
		else if (i == animationStep + 4 || i == animationStep - 4)
			strip.setPixelColor(i, getColorRed(16));
		else if (i == animationStep + 5 || i == animationStep - 5)
			strip.setPixelColor(i, getColorRed(8));
		else
			strip.setPixelColor(i, 0, 0, 0);
	}
	strip.show();
}

void Rampe::drawTronLightPoliceChase() {
	animationStep++;
	if (animationStep == strip.numPixels() + 5)
		animationStep = -5;
	for (int i = 0; i < strip.numPixels(); i++) {
		if (i == animationStep)
			if (animating)
				strip.setPixelColor(i, getColorRed(255));
			else
				strip.setPixelColor(i, getColorBlue(255));

		else if (i == animationStep + 1 || i == animationStep - 1)
			if (animating)
				strip.setPixelColor(i, getColorRed(128));
			else
				strip.setPixelColor(i, getColorBlue(128));
		else if (i == animationStep + 2 || i == animationStep - 2)
			strip.setPixelColor(i, getColorRed(64));
		else if (i == animationStep + 3 || i == animationStep - 3)
			strip.setPixelColor(i, getColorRed(32));
		else if (i == animationStep + 4 || i == animationStep - 4)
			strip.setPixelColor(i, getColorRed(16));
		else if (i == animationStep + 5 || i == animationStep - 5)
			strip.setPixelColor(i, getColorRed(8));
		else
			strip.setPixelColor(i, 0, 0, 0);
	}
	animating = !animating;
	strip.show();
}

void Rampe::drawPoliceChase() {

	animationStep++;
	if (animationStep == strip.numPixels())
		animationStep = 0;

	for (int i = 0; i < strip.numPixels(); i++) {
		if (i < animationStep) {
			strip.setPixelColor(i, getColorRed(64));
		} else if (i == animationStep) {
			if (animating) {
				strip.setPixelColor(i, getColorRed(64));
			} else {
				strip.setPixelColor(i, getColorBlue(255));
				strip.setPixelColor(i - 1, getColorBlue(255));
			}
		} else {
			strip.setPixelColor(i, 0, 0, 0);
		}
	}

	animating = !animating;
	strip.show();
}

uint32_t Rampe::getColorBlue(int brightness) {
	int b = brightness;
	int r = 0; //255 - brightness;
	return strip.Color(r, 0, b);
}

uint32_t Rampe::getColorRed(int brightness) {
	return strip.Color(brightness, 0, 0);
}

uint32_t Rampe::getColorRedToBlue(int brightness) {
	int b = brightness;
	int r = 255 - brightness;
	return strip.Color(r, 0, b);
}

uint32_t Rampe::getColorWhite(int brightness) {
	return strip.Color(brightness, brightness, brightness);
}

uint32_t Rampe::getColorOrange(int brightness) {
	return strip.Color(brightness, brightness * 1 / 3, 0);
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Rampe::Wheel(byte WheelPos) {
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

uint32_t Rampe::getRandomBlueRed(int brightness) {
	switch (random(2)) {
	default:
	case 0:
		return strip.Color(brightness, 0, 0);
	case 1:
		return strip.Color(0, 0, brightness);
	case 2:
		return strip.Color(0, brightness, 0);
	}
}

