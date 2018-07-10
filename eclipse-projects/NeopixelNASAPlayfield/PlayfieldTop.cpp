/*
 * PlayfieldTop.cpp
 *
 *  Created on: 11.02.2016
 *      Author: Oliver
 */

#include "PlayfieldTop.h"

PlayfieldTop::PlayfieldTop(Adafruit_NeoPixel strip) {
	this->strip = strip;
	init();
}

PlayfieldTop::~PlayfieldTop() {
	// TODO Auto-generated destructor stub
}

void PlayfieldTop::init() {
	animating = false;
	animationStep = 0;
	max = strip.numPixels();
}

void PlayfieldTop::drawLauflichtBlau(int millies) {
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

void PlayfieldTop::drawLauflichtBlauBuildingUp(int millies) {
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

void PlayfieldTop::drawEinblenden(int millies) {
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

void PlayfieldTop::drawEinblendenRedBlue(int millies) {
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

void PlayfieldTop::drawAllRed() {
	for (int i = 0; i < strip.numPixels(); i++) {
		strip.setPixelColor(i, getColorRed(255));
	}
	strip.show();
}

uint32_t PlayfieldTop::getColorBlue(int brightness) {
	int b = brightness;
	int r = 0; //255 - brightness;
	return strip.Color(r, 0, b);
}

uint32_t PlayfieldTop::getColorRed(int brightness) {
	return strip.Color(brightness, 0, 0);
}

uint32_t PlayfieldTop::getColorRedToBlue(int brightness) {
	int b = brightness;
	int r = 255 - brightness;
	return strip.Color(r, 0, b);
}

uint32_t PlayfieldTop::getColorOrangeBlue(int brightness, int index) {
	if (index >= 4 && index <= 15) {
		return strip.Color(brightness, brightness * 1 / 3, 0);
	}
	return strip.Color(0, 0, brightness);
}

uint32_t PlayfieldTop::getColorOrange(int brightness) {
	return strip.Color(brightness, brightness * 1 / 3, 0);
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t PlayfieldTop::Wheel(byte WheelPos) {
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
