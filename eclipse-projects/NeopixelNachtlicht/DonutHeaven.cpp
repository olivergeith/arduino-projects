/*
 * DonutHeaven.cpp
 *
 *  Created on: 11.02.2016
 *      Author: Oliver
 */

#include "DonutHeaven.h"

DonutHeaven::DonutHeaven(Adafruit_NeoPixel strip) {
	this->strip = strip;
	init();
}

DonutHeaven::~DonutHeaven() {
	// TODO Auto-generated destructor stub
}

void DonutHeaven::init() {
	animating = false;
	animationStep = 0;
	lauflichtStep = 0;
	laufLichtColor = getColorRed(255);
	max = strip.numPixels();

}

void DonutHeaven::drawWheel(int step) {
	animationStep = animationStep + step;
	if (animationStep >= 256)
		animationStep = 0;
	for (int i = 0; i < strip.numPixels(); i++) {
		strip.setPixelColor(i, Wheel(animationStep));
	}
	strip.show();
}

void DonutHeaven::drawWheelColorful(int step) {
	animationStep = animationStep + step;
	if (animationStep >= 256)
		animationStep = 0;
	for (int i = 0; i < strip.numPixels(); i++) {
		strip.setPixelColor(i, Wheel(animationStep));
	}
	strip.show();
}

void DonutHeaven::drawWheelAllColors(int millies) {
	animationStep = animationStep + 4;
	if (animationStep >= 256)
		animationStep = 0;
	for (int i = 0; i < strip.numPixels(); i++) {
		strip.setPixelColor(i, Wheel(animationStep - i * 256 / strip.numPixels() / 4));
	}
	strip.show();
}

void DonutHeaven::drawLauflichtRandomColor(int millies) {
	if (millies % 25 == 0) {
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

void DonutHeaven::drawLauflichtColorful(int millies) {
	if (millies % 25 == 0) {
		if (lauflichtStep == strip.numPixels()) {
			lauflichtStep = 0;
			laufLichtColor = random(256);
		}

		for (int i = 0; i < strip.numPixels(); i++) {
			if (i == lauflichtStep || i == lauflichtStep - 1) {
				strip.setPixelColor(i, Wheel(laufLichtColor + i * 16));
			} else {
				strip.setPixelColor(i, 0, 0, 0);
			}
		}
		lauflichtStep = lauflichtStep + 1;
		strip.show();
	}
}

void DonutHeaven::drawBarGraphWheeledColorfull(int millies) {
	if (millies % 100 == 0) {
		int center = strip.numPixels() / 2 + 1;
		if (lauflichtStep == center) {
			lauflichtStep = 0;
			laufLichtColor = laufLichtColor + 24;
			if (laufLichtColor >= 256)
				laufLichtColor = 0;
		}
		for (int i = 0; i < strip.numPixels(); i++) {
			if (i <= lauflichtStep || i >= strip.numPixels() - lauflichtStep) {
				strip.setPixelColor(i, Wheel(laufLichtColor + i * 8));
			} else {
				strip.setPixelColor(i, 0, 0, 0);
			}
		}
		lauflichtStep = lauflichtStep + 1;
		strip.show();
	}
}

void DonutHeaven::drawBarGraphWheeled(int millies) {
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

uint32_t DonutHeaven::getRandomColor(int brightness) {
	return Wheel(random(256));
}

uint32_t DonutHeaven::getColorRotGelbGruen(int color) {
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

uint32_t DonutHeaven::getColorRed(int brightness) {
	return strip.Color(brightness, 0, 0);
}

uint32_t DonutHeaven::getColorWhite(int brightness) {
	return strip.Color(brightness, brightness, brightness);
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t DonutHeaven::Wheel(byte WheelPos) {
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
