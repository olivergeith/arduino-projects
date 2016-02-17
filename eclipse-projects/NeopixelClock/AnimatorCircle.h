/*
 * AnimatorCircle.h
 *
 *  Created on: 11.02.2016
 *      Author: Oliver
 */

#ifndef ANIMATORCIRCLE_H_
#define ANIMATORCIRCLE_H_
#include <Adafruit_NeoPixel.h>

enum Style {
	none, fullRotation, doubleHalfRotation
};

class AnimatorCircle {
public:
	AnimatorCircle(Adafruit_NeoPixel strip, int wheelColor, Style style = none);
	virtual ~AnimatorCircle();

	void draw(int newVal);

	void setAnimationStyle(Style style);
	Style getAnimationStyle(void);
	void incrementAnimationStyle(void);
	void decrementAnimationStyle(void);

	void incrementColor(void);
	void decrementColor(void);
	int getWheelColor(void);

	char* getAnimationStyleText(void);
	uint32_t Wheel(byte WheelPos);
	int getRed(byte WheelPos);
	int getGreen(byte WheelPos);
	int getBlue(byte WheelPos);

private:
	int wheelColor;
	int oldVal;
	bool animating;
	Style animationStyle;
	int animationStep;
	Adafruit_NeoPixel strip;
	void setPixel(int index, int wheelColor);
	void drawStyle0(int newVal);
	void drawStyle1(int newVal);
	void drawStyle2(int newVal);
};

#endif /* ANIMATORCIRCLE_H_ */
