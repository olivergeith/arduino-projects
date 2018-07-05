// This is a demonstration on how to use an input device to trigger changes on your neo pixels.
// You should wire a momentary push button to connect from ground to a digital IO pin.  When you
// press the button it will change to a new pixel animation.  Note that you need to press the
// button once to start the first animation!

#include <Adafruit_NeoPixel.h>
#include "Nasa.h"
#include "Williams.h"

// Parameter 1 = number of pixels in strip,  neopixel stick has 8
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream, correct for neopixel stick
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip), correct for neopixel stick
Adafruit_NeoPixel nasaStrip = Adafruit_NeoPixel(39, 7, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel williamsStrip = Adafruit_NeoPixel(20, 6, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel shuttleStrip = Adafruit_NeoPixel(21, 5, NEO_GRB + NEO_KHZ800);

Nasa nasaArea(nasaStrip);
Nasa williamsArea(williamsStrip);
Nasa shuttleArea(shuttleStrip);

int millies = 0;
int deltaMillies = 10;

void setup() {
	millies = 0;
	nasaStrip.setBrightness(255);
	nasaStrip.begin();
	nasaStrip.show(); // Initialize all pixels to 'off'
	williamsStrip.setBrightness(255);
	williamsStrip.begin();
	williamsStrip.show(); // Initialize all pixels to 'off'
	shuttleStrip.setBrightness(255);
	shuttleStrip.begin();
	shuttleStrip.show(); // Initialize all pixels to 'off'

}

void loop() {
	millies = millies + deltaMillies;

	if (millies == 10000)
		millies = 0;

	drawNasa();

	delay(deltaMillies);
}

void drawNasa() {
	if (millies == 0) {
		nasaArea.init();
		williamsArea.init();
		shuttleArea.init();
	} else if (millies < 4000) {
		nasaArea.drawLauflicht(millies);
		williamsArea.drawLauflicht(millies);
		shuttleArea.drawLauflicht(millies);
	} else if (millies == 4000) {
		nasaArea.init();
		williamsArea.init();
		shuttleArea.init();
	} else if (millies < 8000) {
		nasaArea.drawEinblenden(millies);
		williamsArea.drawEinblendenRedBlue(millies);
		shuttleArea.drawEinblendenRedBlue(millies);
	} else if (millies == 8000) {
		nasaArea.init();
		williamsArea.init();
		shuttleArea.init();
	} else {
		nasaArea.drawBlitzeNasa(millies);
		williamsArea.drawBlitzeWilliams(millies);
		shuttleArea.drawBlitzeWilliams(millies);
	}
}

