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

	void drawEinblenden(int millies);
	void drawWheel(int millies);
	void drawLauflicht(int millies);
	void drawEinblendenRedBlue(int millies);
	void drawEinblendenBlueRed(int millies);
	void drawAllRed();
	void drawRandomColors(int millies);
	int max;
	int delta = 1;
	int ms = 0;
	bool animating;
	int animationStep;

	int lauflichtStep = 0;
	uint32_t laufLichtColor;

	uint32_t getRandomBlueWhiteRed(int brightness);
	uint32_t Wheel(byte WheelPos);
	uint32_t getColorBlue(int index);
	uint32_t getColorRed(int index);
	uint32_t getColorRedToBlue(int index);
	uint32_t getColorBlueToRed(int index);
	uint32_t getColorWhite(int brightness);

private:
	Adafruit_NeoPixel strip;

};

#endif
