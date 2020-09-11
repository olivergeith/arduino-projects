/*
 * SpeakerPanel.h
 *
 *  Created on: 11.02.2016
 *      Author: Oliver
 */

#ifndef SpeakerPanel_H_
#define SpeakerPanel_H_
#include <Adafruit_NeoPixel.h>

class SpeakerPanel {
public:
	SpeakerPanel(Adafruit_NeoPixel strip);
	virtual ~SpeakerPanel();

	void init();

	void drawEinblendenGreen();
	void drawEinblenden(int r, int g, int b, int steps);
	void drawWheel(int step);
	void drawWheelColorful(int step);
	void drawWheelAllColors(int step);
	void drawLauflichtRandomColor(int millies);
	void drawLauflichtRotGelbGruen(int millies);
	void drawBarGraphWheeled(int millies);
	void drawBarGraphWheeledColorfull(int millies);
	void drawTronLightBackAndForthWhite();
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
	uint32_t getColorGreen(int brightness);

private:
	Adafruit_NeoPixel strip;

};

#endif
