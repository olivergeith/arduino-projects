/*
 * SpeakerPanel.cpp
 *
 *  Created on: 11.02.2016
 *      Author: Oliver
 */

#include "SpeakerPanel.h"

SpeakerPanel::SpeakerPanel(Adafruit_NeoPixel strip) {
	this->strip = strip;
	init();
}

SpeakerPanel::~SpeakerPanel() {
	// TODO Auto-generated destructor stub
}

void SpeakerPanel::init() {
	animating = false;
	animationStep = 0;
	lauflichtStep = 0;
	laufLichtColor = getColorGreen(255);
	max = strip.numPixels();

}

void SpeakerPanel::drawEinblendenGreen() {
	int steps = 40;

	if (animating)
		animationStep++;
	else
		animationStep--;

	if (animationStep >= 40)
		animating = false;
	if (animationStep <= 0)
		animating = true;

	for (int i = 0; i < strip.numPixels(); i++) {
		strip.setPixelColor(i, getColorGreen(animationStep * 255 / steps));
	}
	strip.show();
}

void SpeakerPanel::drawEinblenden(int r, int g, int b, int steps) {

	if (animating)
		animationStep++;
	else
		animationStep--;

	if (animationStep >= steps)
		animating = false;
	if (animationStep <= 0)
		animating = true;

	for (int i = 0; i < strip.numPixels(); i++) {
		strip.setPixelColor(i, strip.Color( //
				animationStep * r / steps, //
				animationStep * g / steps, //
				animationStep * b / steps));
	}
	strip.show();
}

void SpeakerPanel::drawWheel(int step) {
	animationStep = animationStep + step;
	if (animationStep >= 256)
		animationStep = 0;
	for (int i = 0; i < strip.numPixels(); i++) {
		strip.setPixelColor(i, Wheel(animationStep));
	}
	strip.show();
}

void SpeakerPanel::drawWheelColorful(int step) {
	animationStep = animationStep + step;
	if (animationStep >= 256)
		animationStep = 0;
	for (int i = 0; i < strip.numPixels(); i++) {
		strip.setPixelColor(i, Wheel(animationStep));
	}
	strip.show();
}

void SpeakerPanel::drawWheelAllColors(int step) {
	animationStep = animationStep + step;
	if (animationStep >= 256)
		animationStep = 0;
	for (int i = 0; i < strip.numPixels(); i++) {
		strip.setPixelColor(i, Wheel(animationStep + i * 256 / strip.numPixels() / 3));
	}
	strip.show();
}

void SpeakerPanel::drawLauflichtRandomColor(int millies) {
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

void SpeakerPanel::drawLauflichtRotGelbGruen(int millies) {
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

void SpeakerPanel::drawBarGraphWheeled(int millies) {
	if (millies % 25 == 0) {
		int center = strip.numPixels() / 2 + 1;
		if (lauflichtStep == center) {
			lauflichtStep = 0;
			laufLichtColor = laufLichtColor + 16;
			if (laufLichtColor >= 256)
				laufLichtColor = 0;
		}
		for (int i = 0; i < strip.numPixels(); i++) {
			if (i <= lauflichtStep || i >= strip.numPixels() - lauflichtStep) {
				strip.setPixelColor(i, Wheel(laufLichtColor));
			} else {
				strip.setPixelColor(i, 0, 0, 0);
			}
		}
		lauflichtStep = lauflichtStep + 1;
		strip.show();
	}
}

void SpeakerPanel::drawBarGraphWheeledColorfull(int millies) {
	if (millies % 25 == 0) {
		int center = strip.numPixels() / 2 + 1;
		if (lauflichtStep == center) {
			lauflichtStep = 0;
			laufLichtColor = laufLichtColor + 16;
			if (laufLichtColor >= 256)
				laufLichtColor = 0;
		}
		for (int i = 0; i < strip.numPixels(); i++) {
			if (i <= lauflichtStep || i >= strip.numPixels() - lauflichtStep) {
				strip.setPixelColor(i, Wheel(laufLichtColor + i * 4));
			} else {
				strip.setPixelColor(i, 0, 0, 0);
			}
		}
		lauflichtStep = lauflichtStep + 1;
		strip.show();
	}
}

void SpeakerPanel::drawTronLightBackAndForthWhite() {

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
			strip.setPixelColor(i, getColorWhite(255));
		else if (i == animationStep + 1 || i == animationStep - 1)
			strip.setPixelColor(i, getColorWhite(255));
		else if (i == animationStep + 2 || i == animationStep - 2)
			strip.setPixelColor(i, getColorWhite(128));
		else if (i == animationStep + 3 || i == animationStep - 3)
			strip.setPixelColor(i, getColorWhite(64));
		else if (i == animationStep + 4 || i == animationStep - 4)
			strip.setPixelColor(i, getColorWhite(16));
		else if (i == animationStep + 5 || i == animationStep - 5)
			strip.setPixelColor(i, getColorWhite(8));
		else
			strip.setPixelColor(i, 0, 0, 0);
	}
	strip.show();
}

uint32_t SpeakerPanel::getRandomColor(int brightness) {
	return Wheel(random(256));
}

uint32_t SpeakerPanel::getColorRotGelbGruen(int color) {
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

uint32_t SpeakerPanel::getColorGreen(int brightness) {
	return strip.Color(0, brightness, 0);
}

uint32_t SpeakerPanel::getColorWhite(int brightness) {
	return strip.Color(brightness, brightness, brightness);
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t SpeakerPanel::Wheel(byte WheelPos) {
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
