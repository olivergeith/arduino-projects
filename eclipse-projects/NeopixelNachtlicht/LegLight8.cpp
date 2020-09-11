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

void LegLight8::drawChangingColor(int millies, int step) {
	if (millies % 100 == 0) {
		animationStep = animationStep + step;
		if (animationStep >= 256)
			animationStep = 0;
		for (int i = 0; i < strip.numPixels(); i++) {
			strip.setPixelColor(i, Wheel(animationStep));
		}
		strip.show();
	}
}

void LegLight8::drawRotatingColors(int speed) {
	animationStep = animationStep + speed;
	if (animationStep >= 256)
		animationStep = 0;
	for (int i = 0; i < strip.numPixels(); i++) {
		strip.setPixelColor(i, Wheel(animationStep + i * 256 / strip.numPixels()));
	}
//	strip.setBrightness(200);
	strip.show();
}

void LegLight8::drawDoubleLauflichtWheeled(int millies) {
	if (millies % 50 == 0) {
		animationStep = animationStep + 4;
		if (animationStep >= 256)
			animationStep = 0;

		if (lauflichtStep == strip.numPixels() / 2) {
			lauflichtStep = 0;
			laufLichtColor = Wheel(animationStep);
		}
		for (int i = 0; i < strip.numPixels(); i++) {
			if (i == lauflichtStep || i == strip.numPixels() / 2 + lauflichtStep) {
				strip.setPixelColor(i, laufLichtColor);
			} else {
				strip.setPixelColor(i, 0, 0, 0);
			}
		}
		lauflichtStep = lauflichtStep + 1;
		strip.show();
	}
}

void LegLight8::drawPoliceLight(int millies) {
	if (lauflichtStep == strip.numPixels()) {
		lauflichtStep = 0;
	}
	for (int i = 0; i < strip.numPixels(); i++) {
		if (i == lauflichtStep) {
			strip.setPixelColor(i, 0, 0, 255);
		} else if (i == (strip.numPixels() / 2 + lauflichtStep) % strip.numPixels()) {
			strip.setPixelColor(i, 255, 0, 0);
		} else {
			strip.setPixelColor(i, 0, 0, 0);
		}
	}
	lauflichtStep = lauflichtStep + 1;
	strip.show();
}

void LegLight8::drawLauflichtWheeled(int millies) {
	if (millies % 50 == 0) {
		animationStep = animationStep + 4;
		if (animationStep >= 256)
			animationStep = 0;

		if (lauflichtStep == strip.numPixels()) {
			lauflichtStep = 0;
		}
		for (int i = 0; i < strip.numPixels(); i++) {
			if (i == lauflichtStep) {
				strip.setPixelColor(i, Wheel(animationStep + i));
			} else {
				strip.setPixelColor(i, 0, 0, 0);
			}
		}
		lauflichtStep = lauflichtStep + 1;
		strip.show();
	}
}

void LegLight8::drawRandomSegment(int millies, int modulo) {

	if (millies % modulo == 0) {

		lauflichtStep = random(strip.numPixels());

		animationStep = animationStep + 4;
		if (animationStep >= 256)
			animationStep = 0;

		for (int i = 0; i < strip.numPixels(); i++) {
			if (i == lauflichtStep) {
//				strip.setPixelColor(i, Wheel(animationStep + i));
				strip.setPixelColor(i, getRandomColor(255));
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
