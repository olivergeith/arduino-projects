/*
 * AnimatorCircle.cpp
 *
 *  Created on: 11.02.2016
 *      Author: Oliver
 */

#include "AnimatorCircle.h"

AnimatorCircle::AnimatorCircle(Adafruit_NeoPixel strip, int wheelColor, Style style) {
	this->animationStyle = style;
	this->strip = strip;
	this->wheelColor = wheelColor;
	oldVal = 0;
	animating = false;
	animationStep = 0;
}

AnimatorCircle::~AnimatorCircle() {
	// TODO Auto-generated destructor stub
}

void AnimatorCircle::incrementColor(void) {
	wheelColor++;
	if (wheelColor > 256) {
		wheelColor = 256;
	}
}
void AnimatorCircle::decrementColor(void) {
	wheelColor--;
	if (wheelColor < 0) {
		wheelColor = 0;
	}
}

int AnimatorCircle::getWheelColor(void) {
	return wheelColor;
}

void AnimatorCircle::setAnimationStyle(Style style) {
	this->animationStyle = style;
}

void AnimatorCircle::incrementAnimationStyle(void) {
	switch (animationStyle) {
	default:
	case none:
		animationStyle = doubleHalfRotation;
		break;
	case doubleHalfRotation:
		animationStyle = fullRotation;
		break;
	case fullRotation:
		// nothing
		break;
	}
}
void AnimatorCircle::decrementAnimationStyle(void) {
	switch (animationStyle) {
	default:
	case none:
		// do nothing
		break;
	case doubleHalfRotation:
		animationStyle = none;
		break;
	case fullRotation:
		animationStyle = doubleHalfRotation;
		break;
	}
}

char* AnimatorCircle::getAnimationStyleText(void) {
	switch (animationStyle) {
	default:
	case none:
		return "None";
	case doubleHalfRotation:
		return "Half";
	case fullRotation:
		return "Full";
	}
}

Style AnimatorCircle::getAnimationStyle(void) {
	return animationStyle;
}

void AnimatorCircle::draw(int newVal) {
	switch (animationStyle) {
	default:
	case none:
		drawStyle0(newVal);
		break;
	case fullRotation:
		drawStyle1(newVal);
		break;
	case doubleHalfRotation:
		drawStyle2(newVal);
		break;
	}
}

void AnimatorCircle::drawStyle0(int newVal) {
	if (oldVal != newVal) {
		oldVal = newVal;
	}
	setPixel(newVal, wheelColor);
}

void AnimatorCircle::drawStyle1(int newVal) {
	if (oldVal != newVal) {
		oldVal = newVal;
		animating = true;
		animationStep = 0;
	}
	if (animationStyle == none) {
		animating = false;
	}
	// wenn im Animationg Mode
	if (animating) {
		int index = newVal + animationStep;

		// wir fangen bei der normalen farbe an und z‰hlen die farbe hoch
		uint32_t wheelCol = wheelColor + animationStep * 255 / strip.numPixels();
		// wenn wir beim hochz‰hlen ¸ber 255 kommen, fangen wqir bei 0 wieder an ...ziehen also 255 ab!
		if (wheelCol > 255) {
			wheelCol = wheelCol - 255;
		}
		// dann setzen wir zwei pixel
		setPixel(index - 1, wheelCol);
		setPixel(index, wheelCol);
//		setPixel(index + 1, col);

// n‰chster schritt
		animationStep++;
		// animation fortsetzen ?
		if (animationStep == strip.numPixels()) {
			animating = false;
		}
	} else {
		// sonst ganz normal den Zeiger setzen
		setPixel(newVal, wheelColor);
	}
}

/*
 * von beiden seiten auf den Punkt zu
 */
void AnimatorCircle::drawStyle2(int newVal) {
	int maxi = 30;
	if (oldVal != newVal) {
		oldVal = newVal;
		animating = true;
		animationStep = maxi;
	}
	if (animationStyle == none) {
		animating = false;
	}
	// wenn im Animationg Mode
	if (animating) {
		int index = newVal;

		// wir fangen bei der normalen farbe an und z‰hlen die farbe hoch
		uint32_t wheelCol = wheelColor + animationStep * 255 / maxi;
		// wenn wir beim hochz‰hlen ¸ber 255 kommen, fangen wqir bei 0 wieder an ...ziehen also 255 ab!
		if (wheelCol > 255) {
			wheelCol = wheelCol - 255;
		}
		// dann setzen wir zwei pixel
		setPixel(index + animationStep, wheelCol);
		setPixel(index - animationStep, wheelCol);

		animationStep--;
		// animation fortsetzen ?
		if (animationStep == 0) {
			animating = false;
		}
	} else {
		// sonst ganz normal den Zeiger setzen
		setPixel(newVal, wheelColor);
	}
}

void AnimatorCircle::setPixel(int index, int wheelColor) {
	if (index < 0) {
		index = index + strip.numPixels();
	}
	if (index >= strip.numPixels()) {
		index = index - strip.numPixels();
	}

	// wheelcolor 256 == weiﬂ
	if (wheelColor < 256) {
		strip.setPixelColor(index, Wheel(wheelColor));
	} else {
		strip.setPixelColor(index, 255, 255, 255);
	}
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t AnimatorCircle::Wheel(byte WheelPos) {
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

int AnimatorCircle::getRed(byte WheelPos) {
	WheelPos = 255 - WheelPos;
	if (WheelPos < 85) {
		return 255 - WheelPos * 3;
	}
	if (WheelPos < 170) {
		WheelPos -= 85;
		return 0;
	}
	WheelPos -= 170;
	return WheelPos * 3;
}
int AnimatorCircle::getGreen(byte WheelPos) {
	WheelPos = 255 - WheelPos;
	if (WheelPos < 85) {
		return 0;
	}
	if (WheelPos < 170) {
		WheelPos -= 85;
		return WheelPos * 3;
	}
	WheelPos -= 170;
	return 255 - WheelPos * 3;
}
int AnimatorCircle::getBlue(byte WheelPos) {
	WheelPos = 255 - WheelPos;
	if (WheelPos < 85) {
		return WheelPos * 3;
	}
	if (WheelPos < 170) {
		WheelPos -= 85;
		return 255 - WheelPos * 3;
	}
	WheelPos -= 170;
	return 0;
}

