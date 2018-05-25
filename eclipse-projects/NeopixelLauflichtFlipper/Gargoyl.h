/*
 * Gargoyl.h
 *
 *  Created on: 11.02.2016
 *      Author: Oliver
 */

#ifndef GARGOYL_H_
#define GARGOYL_H_
#include <Adafruit_NeoPixel.h>

class Gargoyl {
public:
	Gargoyl(Adafruit_NeoPixel strip);
	virtual ~Gargoyl();

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
