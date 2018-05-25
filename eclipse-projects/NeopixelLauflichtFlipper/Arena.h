/*
 * Arena.h
 *
 *  Created on: 11.02.2016
 *      Author: Oliver
 */

#ifndef ARENA_H_
#define ARENA_H_
#include <Adafruit_NeoPixel.h>

class Arena {
public:
	Arena(Adafruit_NeoPixel strip);
	virtual ~Arena();

	void draw();

	bool animating;
	int animationStep;

private:
	int delta = 1;

	Adafruit_NeoPixel strip;
	uint32_t Wheel(byte WheelPos);

	uint32_t getColorForIndex(int index);

};

#endif
