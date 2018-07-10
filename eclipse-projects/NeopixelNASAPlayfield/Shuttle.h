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
	void drawShuttleLauflichtBlau(int millies);
	void drawEinblendenRedBlue(int millies);
	void drawTriebwerk(int millies);
	void drawTriebwerkLauflicht(int millies);

	int animationStep;
	boolean flashOn;
	int twSteep;
	int steps;
private:
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
