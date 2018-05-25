/*
 * Monster.h
 *
 *  Created on: 11.02.2016
 *      Author: Oliver
 */

#ifndef MONSTER_H_
#define MONSTER_H_
#include <Adafruit_NeoPixel.h>

class Monster {
public:
	Monster(Adafruit_NeoPixel strip);
	virtual ~Monster();

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
