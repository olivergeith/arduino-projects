/*
 * Shuttle.cpp
 *
 *  Created on: 11.02.2016
 *      Author: Oliver
 */

#include "Shuttle.h"

Shuttle::Shuttle(Adafruit_NeoPixel strip) {
	this->strip = strip;
	init();
}

Shuttle::~Shuttle() {
	// TODO Auto-generated destructor stub
}

void Shuttle::init() {
	animationStep = 0;
	flashOn = false;
	steps = 0;
	twSteep = 0;
}

void Shuttle::drawTriebwerk(int millies) {
	if (ms % 10 == 0) {
		flashOn = !flashOn;
		if (flashOn == true) {
			strip.setPixelColor(0, getColorRed(255));
			strip.setPixelColor(1, getColorRed(255));
			strip.setPixelColor(2, getColorRed(255));
		} else {
			strip.setPixelColor(0, 0, 0, 0);
			strip.setPixelColor(1, 0, 0, 0);
			strip.setPixelColor(2, 0, 0, 0);
		}
	}
}

void Shuttle::drawTriebwerkLauflicht(int millies) {
	if (ms % 30 == 0) {
		twSteep = twSteep + 1;
		if (twSteep == 3)
			twSteep = 0;

		strip.setPixelColor(0, 0, 0, 0);
		strip.setPixelColor(1, 0, 0, 0);
		strip.setPixelColor(2, 0, 0, 0);
		strip.setPixelColor(twSteep, getColorRed(255));
	}
}

void Shuttle::drawShuttleLauflichtBlau(int millies) {
	ms = millies;

	drawTriebwerk(millies);

	strip.setPixelColor(13, getColorBlue(255));

	if (ms % 50 == 0) {
		animationStep++;

		if (animationStep == strip.numPixels())
			animationStep = 3;
		for (int i = strip.numPixels() - 1; i >= 3; i--) {
			if (i == strip.numPixels() + 1 - animationStep) {
				strip.setPixelColor(i, getColorBlue(255));
			} else if (i == strip.numPixels() - animationStep) {
				strip.setPixelColor(i, getColorRed(164));
			} else {
				strip.setPixelColor(i, 0, 0, 0);
			}
		}
	}
	strip.show();
}

void Shuttle::drawEinblendenRedBlue(int millies) {
	int steps = 20;

	drawTriebwerkLauflicht(millies);

	ms = millies;
	if (ms % 6 == 0) {
		animationStep++;
		if (animationStep == 20)
			animationStep = 0;
		for (int i = 3; i < strip.numPixels(); i++) {
			if (animationStep < steps) {
				strip.setPixelColor(i, getColorRedToBlue(animationStep * 255 / steps));
			}
		}
	}
	strip.show();
}

uint32_t Shuttle::getColorBlue(int brightness) {
	int b = brightness;
	int r = 0; //255 - brightness;
	return strip.Color(r, 0, b);
}

uint32_t Shuttle::getColorRed(int brightness) {
	return strip.Color(brightness, 0, 0);
}

uint32_t Shuttle::getColorWhite(int brightness) {
	return strip.Color(brightness, brightness, brightness);
}

uint32_t Shuttle::getColorRedToBlue(int brightness) {
	int r = 255 - brightness;
	int g = 0; //255 - brightness;
	int b = brightness;
	return strip.Color(r, g, b);
}

uint32_t Shuttle::getColorOrangeBlue(int brightness, int index) {
	if (index >= 4 && index <= 15) {
		return strip.Color(brightness, brightness * 1 / 3, 0);
	}
	return strip.Color(0, 0, brightness);
}

uint32_t Shuttle::getColorOrange(int brightness) {
	return strip.Color(brightness, brightness * 1 / 3, 0);
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Shuttle::Wheel(byte WheelPos) {
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
