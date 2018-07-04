/*
 * Krieger.h
 *
 *  Created on: 11.02.2016
 *      Author: Oliver
 */

#ifndef KRIEGER_H_
#define KRIEGER_H_
#include <Adafruit_NeoPixel.h>

class Krieger {
public:
	Krieger(Adafruit_NeoPixel strip);
	virtual ~Krieger();

	void draw();
	void drawFadein();

	bool animating;
	int animationStep;

private:
	int delta = 1;

	Adafruit_NeoPixel strip;
	uint32_t Wheel(byte WheelPos);

	uint32_t getColorForIndex(int index);
	uint32_t getColorForIndex(int index, int brightness);

};

#endif
