/*
 * LegLight8.cpp
 *
 *  Created on: 11.02.2016
 *      Author: Oliver
 */

#include "LegLight8.h"

LegLight8::LegLight8(Adafruit_NeoPixel strip) {
	this->strip = strip;
	init();
}

LegLight8::~LegLight8() {
	// TODO Auto-generated destructor stub
}

void LegLight8::init() {
	animating = false;
	animationStep = 0;
	lauflichtStep = 0;
	laufLichtColor = getColorRed(255);
	max = strip.numPixels();

}

void LegLight8::drawEinblendenRed(int millies) {
	int steps = 20;
	ms = millies;
	if (ms % 25 == 0) {
		animationStep++;
		if (animationStep == 70)
			animationStep = 0;
		for (int i = 0; i < strip.numPixels(); i++) {
			if (animationStep < steps) {
				strip.setPixelColor(i, getColorRed(animationStep * 255 / steps));
			} else {
				strip.setPixelColor(i, getColorRed(255));
			}
		}
	}
	strip.show();
}

void LegLight8::drawWheel(int step) {
	animationStep = animationStep + step;
	if (animationStep >= 256)
		animationStep = 0;
	for (int i = 0; i < strip.numPixels(); i++) {
		strip.setPixelColor(i, Wheel(animationStep));
	}
	strip.show();
}

void LegLight8::drawWheelColorful(int step) {
	animationStep = animationStep + step;
	if (animationStep >= 256)
		animationStep = 0;
	for (int i = 0; i < strip.numPixels(); i++) {
		strip.setPixelColor(i, Wheel(animationStep + i));
	}
	strip.show();
}

void LegLight8::drawWheelAllColors(int millies) {
	animationStep = animationStep + 4;
	if (animationStep >= 256)
		animationStep = 0;
	for (int i = 0; i < strip.numPixels(); i++) {
		strip.setPixelColor(i, Wheel(animationStep + i * 256 / strip.numPixels() / 3));
	}
	strip.show();
}

void LegLight8::drawLauflichtRandomColor(int millies) {
	if (millies % 50 == 0) {
		if (lauflichtStep == strip.numPixels()) {
			lauflichtStep = 0;
			laufLichtColor = getRandomColor(255);
		}
		for (int i = 0; i < strip.numPixels(); i++) {
			if (i == lauflichtStep || i == lauflichtStep - 1) {
				strip.setPixelColor(i, laufLichtColor);
			} else {
				strip.setPixelColor(i, 0, 0, 0);
			}
		}
		lauflichtStep = lauflichtStep + 1;
		strip.show();
	}
}

void LegLight8::drawLauflichtRotGelbGruen(int millies) {
	if (millies % 50 == 0) {
		if (lauflichtStep == strip.numPixels()) {
			lauflichtStep = 0;
			animationStep++;
			if (animationStep == 3)
				animationStep = 0;
		}
		for (int i = 0; i < strip.numPixels(); i++) {
			if (i == lauflichtStep || i == lauflichtStep - 1) {
				strip.setPixelColor(i, getColorRotGelbGruen(animationStep));
			} else {
				strip.setPixelColor(i, 0, 0, 0);
			}
		}
		lauflichtStep = lauflichtStep + 1;
		strip.show();
	}
}

void LegLight8::drawBarGraphWheeled(int millies) {
	if (millies % 100 == 0) {
		if (lauflichtStep == strip.numPixels()) {
			lauflichtStep = 0;
			laufLichtColor = laufLichtColor + 16;
			if (laufLichtColor >= 256)
				laufLichtColor = 0;
		}
		for (int i = 0; i < strip.numPixels(); i++) {
			if (i <= lauflichtStep) {
				strip.setPixelColor(i, Wheel(laufLichtColor));
			} else {
				strip.setPixelColor(i, 0, 0, 0);
			}
		}
		lauflichtStep = lauflichtStep + 1;
		strip.show();
	}
}

uint32_t LegLight8::getRandomColor(int brightness) {
	return Wheel(random(256));
}

uint32_t LegLight8::getColorRotGelbGruen(int color) {
	switch (color) {
	default:
	case 0:
		return Wheel(0);
	case 1:
		return Wheel(16);
	case 2:
		return Wheel(64);

	}
}

uint32_t LegLight8::getColorRed(int brightness) {
	return strip.Color(brightness, 0, 0);
}

uint32_t LegLight8::getColorWhite(int brightness) {
	return strip.Color(brightness, brightness, brightness);
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t LegLight8::Wheel(byte WheelPos) {
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
