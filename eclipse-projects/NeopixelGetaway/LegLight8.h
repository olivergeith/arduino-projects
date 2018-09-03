/*
 * LegLight8.h
 *
 *  Created on: 11.02.2016
 *      Author: Oliver
 */

#ifndef LegLight8_H_
#define LegLight8_H_
#include <Adafruit_NeoPixel.h>

class LegLight8 {
public:
	LegLight8(Adafruit_NeoPixel strip);
	virtual ~LegLight8();

	void init();

	void drawEinblendenRed(int millies);
	void drawWheel(int millies);
	void drawWheelAllColors(int millies);
	void drawLauflichtRandomColor(int millies);
	void drawLauflichtRotGelbGruen(int millies);
	void drawBarGraphWheeled(int millies);
	int max;
	int delta = 1;
	int ms = 0;
	bool animating;
	int animationStep;

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
