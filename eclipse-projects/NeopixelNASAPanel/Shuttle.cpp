/*
 * Shuttle.cpp
 *
 *  Created on: 11.02.2016
 *      Author: Oliver
 */

#include "Shuttle.h"

Shuttle::Shuttle(Adafruit_NeoPixel strip) {
	this->strip = strip;
	animating = false;
	animationStep = 0;
	speed = 100;
}

Shuttle::~Shuttle() {
	// TODO Auto-generated destructor stub
}

void Shuttle::init() {
	animationStep = 0;
	speed = 100;
}

void Shuttle::drawLauflichtBlauSchneller(int millies) {
	ms = millies;
	if (ms % speed == 0) {
		animationStep++;
		if (animationStep == strip.numPixels()) {
			animationStep = 0;
			if (speed > 20)
				speed = speed - 10;
		}
		for (int i = 0; i < strip.numPixels(); i++) {
			if (i == animationStep) {
				strip.setPixelColor(i, getColorBlue(255));
			} else if (i == animationStep - 1) {
				strip.setPixelColor(i, getColorBlue(42));
			} else if (i == animationStep - 2) {
				strip.setPixelColor(i, getColorBlue(16));
			} else {
				strip.setPixelColor(i, 0, 0, 0);
			}
		}
	}
	strip.show();
}

void Shuttle::drawLauflichtBlau(int millies) {
	ms = millies;
	if (ms % 50 == 0) {
		animationStep++;
		if (animationStep == strip.numPixels())
			animationStep = 0;
		for (int i = 0; i < strip.numPixels(); i++) {
			if (i == animationStep) {
				strip.setPixelColor(i, getColorBlue(255));
			} else if (i == animationStep + 1 || i == animationStep - 1) {
				strip.setPixelColor(i, getColorBlue(32));
			} else if (i == animationStep + 2 || i == animationStep - 2) {
				strip.setPixelColor(i, getColorBlue(10));
			} else {
				strip.setPixelColor(i, 0, 0, 0);
			}
		}
	}
	strip.show();
}
void Shuttle::drawLauflichtRot(int millies) {
	ms = millies;
	if (ms % 50 == 0) {
		animationStep++;
		if (animationStep == strip.numPixels())
			animationStep = 0;
		for (int i = 0; i < strip.numPixels(); i++) {
			if (i == animationStep || i == animationStep + 1) {
				strip.setPixelColor(i, getColorRed(255));
			} else {
				strip.setPixelColor(i, 0, 0, 0);
			}
		}
	}
	strip.show();
}
void Shuttle::drawLauflichtWeiss(int millies) {
	ms = millies;
	if (ms % 50 == 0) {
		animationStep++;
		if (animationStep == strip.numPixels())
			animationStep = 0;
		for (int i = 0; i < strip.numPixels(); i++) {
			if (i == animationStep || i == animationStep + 1) {
				strip.setPixelColor(i, getColorWhite(128));
			} else {
				strip.setPixelColor(i, 0, 0, 0);
			}
		}
	}
	strip.show();
}

void Shuttle::drawEinblenden(int millies) {
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

void Shuttle::drawEinblendenRedBlue(int millies) {
	int steps = 20;
	ms = millies;
	if (ms % 10 == 0) {
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
