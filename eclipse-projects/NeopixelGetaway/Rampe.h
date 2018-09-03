/*
 * RampeHinten.h
 *
 *  Created on: 11.02.2016
 *      Author: Oliver
 */

#ifndef PLAYFIELD_TOP_H_
#define PLAYFIELD_TOP_H_
#include <Adafruit_NeoPixel.h>

class Rampe {
public:
	Rampe(Adafruit_NeoPixel strip);
	virtual ~Rampe();

	void init();
	void drawLauflichtBlau(int millies);
	void drawLauflichtBlauBuildingUp(int millies);

	void drawEinblenden(int millies);
	void drawEinblendenRedBlue(int millies);
	void drawTronLightWhite();
	void drawTronLightRed();
	void drawTronLightPoliceChase();
	void drawPoliceChase();
	int max;
	int delta = 1;
	int ms = 0;
	bool animating;
	int animationStep;
	uint32_t Wheel(byte WheelPos);
	uint32_t getColorBlue(int index);
	uint32_t getColorRed(int index);
	uint32_t getColorRedToBlue(int index);
	uint32_t getColorOrange(int brightness);
	uint32_t getColorWhite(int brightness);
	uint32_t getRandomBlueRed(int brightness);

private:
	Adafruit_NeoPixel strip;

};

#endif
