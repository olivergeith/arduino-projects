// This is a demonstration on how to use an input device to trigger changes on your neo pixels.
// You should wire a momentary push button to connect from ground to a digital IO pin.  When you
// press the button it will change to a new pixel animation.  Note that you need to press the
// button once to start the first animation!

#include <Adafruit_NeoPixel.h>
#include "Nasa.h"
#include "Shuttle.h"

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
Adafruit_NeoPixel spaceShuttleStrip = Adafruit_NeoPixel(10, 4, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel playfieldTopStrip = Adafruit_NeoPixel(31, 3, NEO_GRB + NEO_KHZ800);

Nasa nasaLogoArea(nasaStrip);
Nasa williamsLogoArea(williamsStrip);
Nasa shuttleLogoArea(shuttleStrip);

Shuttle spaceShuttleArea(spaceShuttleStrip);

Nasa playfieldTopArea(playfieldTopStrip);

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
	spaceShuttleStrip.setBrightness(255);
	spaceShuttleStrip.begin();
	spaceShuttleStrip.show(); // Initialize all pixels to 'off'
	playfieldTopStrip.setBrightness(255);
	playfieldTopStrip.begin();
	playfieldTopStrip.show(); // Initialize all pixels to 'off'

}

void loop() {
	millies = millies + deltaMillies;

	if (millies == 10000)
		millies = 0;

	drawNasa();
	drawSpaceShuttleRamp();
	drawPlayfield();
	delay(deltaMillies);
}

void drawNasa() {
	if (millies == 0) {
		nasaLogoArea.init();
		williamsLogoArea.init();
		shuttleLogoArea.init();
	} else if (millies < 4000) {
		nasaLogoArea.drawLauflichtBlau(millies);
		williamsLogoArea.drawLauflichtBlau(millies);
		shuttleLogoArea.drawLauflichtBlau(millies);
	} else if (millies == 4000) {
		nasaLogoArea.init();
		williamsLogoArea.init();
		shuttleLogoArea.init();
	} else if (millies < 8000) {
		nasaLogoArea.drawEinblenden(millies);
		williamsLogoArea.drawEinblendenRedBlue(millies);
		shuttleLogoArea.drawEinblendenRedBlue(millies);
	} else if (millies == 8000) {
		nasaLogoArea.init();
		williamsLogoArea.init();
		shuttleLogoArea.init();
	} else {
		nasaLogoArea.drawBlitzeNasa(millies);
		williamsLogoArea.drawBlitzeWilliams(millies);
		shuttleLogoArea.drawBlitzeWilliams(millies);
	}
}

void drawSpaceShuttle() {
	if (millies == 0) {
		spaceShuttleArea.init();
	} else if (millies < 7000) {
		spaceShuttleArea.drawLauflichtBlau(millies);
	} else if (millies == 7000) {
		spaceShuttleArea.init();
	} else if (millies < 8000) {
		spaceShuttleArea.drawLauflichtRot(millies);
//		spaceShuttleArea.drawEinblenden(millies);
	} else if (millies == 8000) {
		spaceShuttleArea.init();
	} else {
//		spaceShuttleArea.drawLauflichtWeiss(millies);
		spaceShuttleArea.drawEinblendenRedBlue(millies);
	}
}

void drawSpaceShuttleRamp() {
	if (millies == 0) {
		spaceShuttleArea.init();
	} else
		spaceShuttleArea.drawLauflichtBlau(millies);
}

void drawPlayfield() {
	if (millies == 0) {
		playfieldTopArea.init();
	} else {
		playfieldTopArea.drawLauflichtBlauBuildingUp(millies);
	}
}
/*
 void drawPlayfield() {
 if (millies == 0) {
 playfieldTopArea.init();
 } else if (millies < 5000) {
 playfieldTopArea.drawLauflichtBlauBuildingUp(millies);
 } else if (millies == 5000) {
 playfieldTopArea.init();
 } else if (millies < 7500) {
 playfieldTopArea.drawEinblenden(millies);
 } else if (millies == 7500) {
 playfieldTopArea.init();
 } else {
 //		spaceShuttleArea.drawLauflichtWeiss(millies);
 playfieldTopArea.drawEinblendenRedBlue(millies);
 }
 }
 */
