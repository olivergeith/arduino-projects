// This is a demonstration on how to use an input device to trigger changes on your neo pixels.
// You should wire a momentary push button to connect from ground to a digital IO pin.  When you
// press the button it will change to a new pixel animation.  Note that you need to press the
// button once to start the first animation!

#include <Adafruit_NeoPixel.h>

#include "Rampe.h"
#include "LegLight8.h"

// Parameter 1 = number of pixels in strip,  neopixel stick has 8
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream, correct for neopixel stick
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip), correct for neopixel stick
Adafruit_NeoPixel rampeHintenStrip = Adafruit_NeoPixel(15, 6, NEO_GRB + NEO_KHZ800);
Rampe rampeHinten(rampeHintenStrip);
Adafruit_NeoPixel rampeObenStrip = Adafruit_NeoPixel(31, 7, NEO_GRB + NEO_KHZ800);
Rampe rampeOben(rampeObenStrip);
Adafruit_NeoPixel rampeBahnStrip = Adafruit_NeoPixel(18, 5, NEO_GRB + NEO_KHZ800);
Rampe rampeBahn(rampeBahnStrip);

Adafruit_NeoPixel legVLStrip = Adafruit_NeoPixel(8, 4, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel legVRStrip = Adafruit_NeoPixel(8, 3, NEO_GRB + NEO_KHZ800);
LegLight8 legVL(legVLStrip);
LegLight8 legVR(legVRStrip);

Adafruit_NeoPixel legHLStrip = Adafruit_NeoPixel(6, 2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel legHRStrip = Adafruit_NeoPixel(6, 1, NEO_GRB + NEO_KHZ800);
LegLight8 legHL(legHLStrip);
LegLight8 legHR(legHRStrip);

Adafruit_NeoPixel button1Strip = Adafruit_NeoPixel(8, 8, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel button2Strip = Adafruit_NeoPixel(8, 9, NEO_GRB + NEO_KHZ800);
LegLight8 button1(button1Strip);
LegLight8 button2(button2Strip);

Adafruit_NeoPixel outHoleStrip = Adafruit_NeoPixel(12, 10, NEO_GRB + NEO_KHZ800);
LegLight8 outHole(outHoleStrip);

int millies = 0;
int deltaMillies = 25;

void setup() {

	millies = 0;
	rampeObenStrip.setBrightness(255);
	rampeObenStrip.begin();
	rampeObenStrip.show(); // Initialize all pixels to 'off'
	rampeHintenStrip.setBrightness(255);
	rampeHintenStrip.begin();
	rampeHintenStrip.show(); // Initialize all pixels to 'off'
	rampeBahnStrip.setBrightness(255);
	rampeBahnStrip.begin();
	rampeBahnStrip.show(); // Initialize all pixels to 'off'
	legVLStrip.setBrightness(255);
	legVLStrip.begin();
	legVLStrip.show(); // Initialize all pixels to 'off'
	legVRStrip.setBrightness(255);
	legVRStrip.begin();
	legVRStrip.show(); // Initialize all pixels to 'off'
	legHLStrip.setBrightness(255);
	legHLStrip.begin();
	legHLStrip.show(); // Initialize all pixels to 'off'
	legHRStrip.setBrightness(255);
	legHRStrip.begin();
	legHRStrip.show(); // Initialize all pixels to 'off'

	button1Strip.setBrightness(255);
	button1Strip.begin();
	button1Strip.show(); // Initialize all pixels to 'off'
	button2Strip.setBrightness(255);
	button2Strip.begin();
	button2Strip.show(); // Initialize all pixels to 'off'

	outHoleStrip.setBrightness(255);
	outHoleStrip.begin();
	outHoleStrip.show(); // Initialize all pixels to 'off'

}

void loop() {
	millies = millies + deltaMillies;

	if (millies >= 10000)
		millies = 0;

	drawRampen();
	drawLegs2();
	delay(deltaMillies);
}

void drawRampen() {
	if (millies == 0 || millies == 7000) {
		rampeOben.init();
		rampeBahn.init();
		rampeHinten.init();
	} else if (millies < 7000) {
		rampeOben.drawTronLightWhite();
		rampeBahn.drawTronLightWhite();
		rampeHinten.drawTronLightWhite();
	} else {
		rampeOben.drawTronLightPoliceChase();
		rampeBahn.drawTronLightPoliceChase();
		rampeHinten.drawTronLightPoliceChase();
	}
	outHole.drawWheelColorful(1);
}

int legMode = 3;

void drawLegs2() {
	if (millies == 0) {
		legMode++;
		if (legMode == 4)
			legMode = 0;
		legVL.init();
		legVR.init();
		legHL.init();
		legHR.init();
		button1.init();
		button2.init();
	}
	switch (legMode) {
	default:
	case 0:
		legVL.drawLauflichtRotGelbGruen(millies);
		legVR.drawLauflichtRotGelbGruen(millies);
		legHL.drawLauflichtRotGelbGruen(millies);
		legHR.drawLauflichtRotGelbGruen(millies);
		button1.drawLauflichtRotGelbGruen(millies);
		button2.drawLauflichtRotGelbGruen(millies);
		break;
	case 1:
		legVL.drawWheel(2);
		legVR.drawWheel(2);
		legHL.drawWheel(2);
		legHR.drawWheel(2);
		button1.drawWheel(2);
		button2.drawWheel(2);
		break;
	case 2:
		legVL.drawWheelAllColors(millies);
		legVR.drawWheelAllColors(millies);
		legHL.drawWheelAllColors(millies);
		legHR.drawWheelAllColors(millies);
		button1.drawWheelAllColors(millies);
		button2.drawWheelAllColors(millies);
		break;
	case 3:
		legVL.drawBarGraphWheeled(millies);
		legVR.drawBarGraphWheeled(millies);
		legHL.drawBarGraphWheeled(millies);
		legHR.drawBarGraphWheeled(millies);
		button1.drawBarGraphWheeled(millies);
		button2.drawBarGraphWheeled(millies);
		break;

	}

}

