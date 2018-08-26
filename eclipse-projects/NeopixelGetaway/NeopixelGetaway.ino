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

}

void loop() {
	millies = millies + deltaMillies;

	if (millies >= 10000)
		millies = 0;

	drawRampeOben();
	drawRampeHinten();
	drawRampeBahn();
	drawLegs2();
	delay(deltaMillies);
}

void drawRampeOben() {
	if (millies == 0) {
		rampeOben.init();
	} else {
		rampeOben.drawTronLight();
	}
}

void drawRampeHinten() {
	if (millies == 0) {
		rampeHinten.init();
	} else {
		//rampeHinten.drawTronLight();
		rampeHinten.drawTronLight();
	}
}
void drawRampeBahn() {
	if (millies == 0 || millies == 6000) {
		rampeBahn.init();
	} else if (millies < 6000) {
		rampeBahn.drawTronLight();
	} else {
		rampeBahn.drawPoliceChase();
	}
}

void drawLegs() {
	if (millies == 0 || millies == 6000) {
		legVL.init();
		legVR.init();
	} else if (millies < 6000) {
		legVL.drawWheel2(millies);
		legVR.drawWheel2(millies);
	} else {
		legVL.drawLauflicht(millies);
		legVR.drawLauflicht(millies);
	}
}

int legMode = 3;

void drawLegs2() {
	if (millies == 0) {
		legMode = random(4);
		legVL.init();
		legVR.init();
	}
	switch (legMode) {
	default:
	case 0:
		legVL.drawLauflicht(millies);
		legVR.drawLauflicht(millies);
		legHL.drawLauflicht(millies);
		legHR.drawLauflicht(millies);
		break;
	case 1:
		legVL.drawWheel(millies);
		legVR.drawWheel(millies);
		legHL.drawWheel(millies);
		legHR.drawWheel(millies);
		break;
	case 2:
		legVL.drawWheel2(millies);
		legVR.drawWheel2(millies);
		legHL.drawWheel2(millies);
		legHR.drawWheel2(millies);
		break;
	case 3:
		legVL.drawBarGraphWheeled(millies);
		legVR.drawBarGraphWheeled(millies);
		legHL.drawBarGraphWheeled(millies);
		legHR.drawBarGraphWheeled(millies);
		break;

	}

}

