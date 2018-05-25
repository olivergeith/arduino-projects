/*
 * Kriegerin.h
 *
 *  Created on: 11.02.2016
 *      Author: Oliver
 */

#ifndef KRIEGERIN_H_
#define KRIEGERIN_H_
#include <Adafruit_NeoPixel.h>

class Kriegerin {
public:
	Kriegerin(Adafruit_NeoPixel strip);
	virtual ~Kriegerin();

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
