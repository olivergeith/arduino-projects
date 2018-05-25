/*
 * AnimatedArea.h
 *
 *  Created on: 11.02.2016
 *      Author: Oliver
 */

#ifndef ANIMATEDAREA_H_
#define ANIMATEDAREA_H_
#include <Adafruit_NeoPixel.h>

class AnimatedArea {
public:
	AnimatedArea(Adafruit_NeoPixel strip);
	virtual ~AnimatedArea();

	void draw();

	bool animating;
	int animationStep;

private:
	int delta = 1;

	Adafruit_NeoPixel strip;

	uint32_t Wheel(byte WheelPos);

};

#endif /* ANIMATEDAREA_H_ */
