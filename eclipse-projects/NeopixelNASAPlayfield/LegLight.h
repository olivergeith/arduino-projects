/*
 * LegLight.h
 *
 *  Created on: 11.02.2016
 *      Author: Oliver
 */

#ifndef LEGLIGHT_H_
#define LEGLIGHT_H_
#include <Adafruit_NeoPixel.h>

class LegLight {
public:
	LegLight(Adafruit_NeoPixel strip);
	virtual ~LegLight();

	void init();
	void drawLauflicht(int millies, int r, int g, int b);
	void drawLauflicht2(int millies);

	void drawEinblenden(int millies);
	void drawEinblendenRedBlue(int millies);
	void drawAllRed();
	int max;
	int delta = 1;
	int ms = 0;
	bool animating;
	int animationStep;
	uint32_t Wheel(byte WheelPos);
	uint32_t getColorBlue(int index);
	uint32_t getColorRed(int index);
	uint32_t getColorRedToBlue(int index);
	uint32_t getColorWhite(int brightness);

private:
	Adafruit_NeoPixel strip;

};

#endif
