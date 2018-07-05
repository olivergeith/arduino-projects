/*
 * Nasa.h
 *
 *  Created on: 11.02.2016
 *      Author: Oliver
 */

#ifndef NASA_H_
#define NASA_H_
#include <Adafruit_NeoPixel.h>

class Nasa {
public:
	Nasa(Adafruit_NeoPixel strip);
	virtual ~Nasa();

	void init();
	void drawLauflicht(int millies);
	void drawEinblenden(int millies);
	void drawEinblendenRedBlue(int millies);
	void drawBlitzeNasa(int millies);
	void drawBlitzeWilliams(int millies);

	bool animating;
	int animationStep;

private:
	int delta = 1;
	int ms = 0;

	Adafruit_NeoPixel strip;
	uint32_t Wheel(byte WheelPos);

	uint32_t getColorBlue(int index);
	uint32_t getColorRedToBlue(int index);
	uint32_t getColorOrange(int brightness);
	uint32_t getColorOrangeBlue(int brightness, int index);

};

#endif
