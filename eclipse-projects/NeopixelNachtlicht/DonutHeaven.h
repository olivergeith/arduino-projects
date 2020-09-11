/*
 * DonutHeaven.h
 *
 *  Created on: 11.02.2016
 *      Author: Oliver
 */

#ifndef DonutHeaven_H_
#define DonutHeaven_H_
#include <Adafruit_NeoPixel.h>

class DonutHeaven {
public:
	DonutHeaven(Adafruit_NeoPixel strip);
	virtual ~DonutHeaven();

	void init();

	void drawWheel(int step);
	void drawWheelColorful(int step);
	void drawWheelAllColors(int millies);
	void drawLauflichtRandomColor(int millies);
	void drawLauflichtColorful(int millies);
	void drawBarGraphWheeled(int millies);
	void drawBarGraphWheeledColorfull(int millies);
	int max;
	int delta = 1;
	int ms = 0;
	bool animating;
	int animationStep;
	int anzLetters = 11;

	int lauflichtStep = 0;
	uint32_t laufLichtColor;

	uint32_t getRandomColor(int brightness);
	uint32_t getColorRotGelbGruen(int brightness);
	uint32_t Wheel(byte WheelPos);
	uint32_t getColorWhite(int brightness);
	uint32_t getColorRed(int brightness);

private:
	Adafruit_NeoPixel strip;

};

#endif
