/*
 * Shuttle.h
 *
 *  Created on: 11.02.2016
 *      Author: Oliver
 */

#ifndef SHUTTLE_H_
#define SHUTTLE_H_
#include <Adafruit_NeoPixel.h>

class Shuttle {
public:
	Shuttle(Adafruit_NeoPixel strip);
	virtual ~Shuttle();

	void init();
	void drawLauflichtBlauSchneller(int millies);
	void drawLauflichtBlau(int millies);
	void drawLauflichtRot(int millies);
	void drawLauflichtWeiss(int millies);
	void drawEinblenden(int millies);
	void drawEinblendenRedBlue(int millies);

	bool animating;
	int animationStep;
	int speed;

private:
	int delta = 1;
	int ms = 0;

	Adafruit_NeoPixel strip;
	uint32_t Wheel(byte WheelPos);

	uint32_t getColorBlue(int index);
	uint32_t getColorRed(int index);
	uint32_t getColorWhite(int index);
	uint32_t getColorRedToBlue(int index);
	uint32_t getColorOrange(int brightness);
	uint32_t getColorOrangeBlue(int brightness, int index);

};

#endif
