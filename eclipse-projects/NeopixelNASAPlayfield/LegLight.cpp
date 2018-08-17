/*
 * LegLight.cpp
 *
 *  Created on: 11.02.2016
 *      Author: Oliver
 */

#include "LegLight.h"

LegLight::LegLight(Adafruit_NeoPixel strip) {
	this->strip = strip;
	init();
}

LegLight::~LegLight() {
	// TODO Auto-generated destructor stub
}

void LegLight::init() {
	animating = false;
	animationStep = 0;
	lauflichtStep = 0;
	laufLichtColor = getColorRed(255);
	max = strip.numPixels();

}

void LegLight::drawEinblenden(int millies) {
	int steps = 20;
	ms = millies;
	if (ms % 20 == 0) {
		animationStep++;
		if (animationStep == 70)
			animationStep = 0;
		for (int i = 0; i < strip.numPixels(); i++) {
			if (animationStep < steps) {
				strip.setPixelColor(i, getColorBlue(animationStep * 255 / steps));
			} else {
				strip.setPixelColor(i, getColorBlue(255));
			}
		}
	}
	strip.show();
}

void LegLight::drawWheel(int millies) {
	int steps = 20;
	ms = millies;
	if (ms % 60 == 0) {
		animationStep++;
		if (animationStep == 70)
			animationStep = 0;
		for (int i = 0; i < strip.numPixels(); i++) {
			strip.setPixelColor(i, Wheel(i + animationStep * 255 / steps));
		}
	}
	strip.show();
}

void LegLight::drawEinblendenRedBlue(int millies) {
	int steps = 20;
	ms = millies;
	if (ms % 16 == 0) {
		animationStep++;
		if (animationStep == 20)
			animationStep = 0;
		for (int i = 0; i < strip.numPixels(); i++) {
			if (animationStep < steps) {
				strip.setPixelColor(i, getColorRedToBlue(animationStep * 255 / steps));
			}
		}
	}
	strip.show();
}

void LegLight::drawEinblendenBlueRed(int millies) {
	int steps = 20;
	ms = millies;
	if (ms % 16 == 0) {
		animationStep++;
		if (animationStep == 20)
			animationStep = 0;
		for (int i = 0; i < strip.numPixels(); i++) {
			if (animationStep < steps) {
				strip.setPixelColor(i, getColorBlueToRed(animationStep * 255 / steps));
			}
		}
	}
	strip.show();
}

void LegLight::drawLauflicht(int millies) {
	if (millies % 20 == 0) {
		if (lauflichtStep == strip.numPixels()) {
			lauflichtStep = 0;
			laufLichtColor = getRandomBlueWhiteRed(255);
		}
		for (int i = 0; i < strip.numPixels(); i++) {
			if (i == lauflichtStep || i == lauflichtStep - 1) {
				strip.setPixelColor(i, laufLichtColor);
			} else {
				strip.setPixelColor(i, 0, 0, 0);
			}
		}
		lauflichtStep = lauflichtStep + 1;
	}
	strip.show();
}

void LegLight::drawRandomColors(int millies) {
	if (millies % 50 == 0) {
		for (int i = 0; i < strip.numPixels(); i++) {
			strip.setPixelColor(i, getRandomBlueWhiteRed(255));
		}
	}
	strip.show();
}

void LegLight::drawAllRed() {
	for (int i = 0; i < strip.numPixels(); i++) {
		strip.setPixelColor(i, getColorRed(255));
	}
	strip.show();
}

uint32_t LegLight::getColorBlue(int brightness) {
	int b = brightness;
	int r = 0; //brightness * 0.3f;
	int g = 0; //brightness * 0.99f;
	return strip.Color(r, g, b);
}

uint32_t LegLight::getRandomBlueWhiteRed(int brightness) {
	switch (random(3)) {
	default:
	case 0:
		return strip.Color(brightness, 0, 0);
	case 1:
		return strip.Color(brightness, brightness, brightness);
	case 2:
		return strip.Color(0, 0, brightness);
	case 3:
		return strip.Color(0, brightness, 0);
	}
}

uint32_t LegLight::getColorRed(int brightness) {
	return strip.Color(brightness, 0, 0);
}

uint32_t LegLight::getColorRedToBlue(int brightness) {
	int b = brightness;
	int g = 0; //brightness;
	int r = 255 - brightness;
	return strip.Color(r, g, b);
}
uint32_t LegLight::getColorBlueToRed(int brightness) {
	int r = brightness;
	int b = 255 - brightness;
	return strip.Color(r, 0, b);
}

uint32_t LegLight::getColorWhite(int brightness) {
	return strip.Color(brightness, brightness, brightness);
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t LegLight::Wheel(byte WheelPos) {
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
