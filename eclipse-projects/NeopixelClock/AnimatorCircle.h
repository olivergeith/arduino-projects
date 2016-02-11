/*
 * AnimatorCircle.h
 *
 *  Created on: 11.02.2016
 *      Author: Oliver
 */

#ifndef ANIMATORCIRCLE_H_
#define ANIMATORCIRCLE_H_
#include <Adafruit_NeoPixel.h>

class AnimatorCircle {
public:
	AnimatorCircle(Adafruit_NeoPixel strip, uint32_t color,
			boolean hasAnimation = true);
	virtual ~AnimatorCircle();
	void draw(int newVal);
private:
	uint32_t color;
	int oldVal;
	bool animating;
	boolean hasAnimation;
	int animationStep;
	Adafruit_NeoPixel strip;
	uint32_t Wheel(byte WheelPos);
};

#endif /* ANIMATORCIRCLE_H_ */
