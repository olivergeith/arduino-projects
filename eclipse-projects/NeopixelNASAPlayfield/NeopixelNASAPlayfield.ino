// This is a demonstration on how to use an input device to trigger changes on your neo pixels.
// You should wire a momentary push button to connect from ground to a digital IO pin.  When you
// press the button it will change to a new pixel animation.  Note that you need to press the
// button once to start the first animation!

#include <Adafruit_NeoPixel.h>

#include "PlayfieldTop.h"
#include "Shuttle.h"
#include "LegLight.h"

// Parameter 1 = number of pixels in strip,  neopixel stick has 8
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream, correct for neopixel stick
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip), correct for neopixel stick
Adafruit_NeoPixel spaceShuttleStrip = Adafruit_NeoPixel(14, 7, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel playfieldTopStrip = Adafruit_NeoPixel(31, 6, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel legStrip = Adafruit_NeoPixel(6, 5, NEO_GRB + NEO_KHZ800);

const int flashPin = 2;     // the number of the pushbutton pin

Shuttle spaceShuttleArea(spaceShuttleStrip);
PlayfieldTop playfieldTopArea(playfieldTopStrip);
LegLight legArea(legStrip);

int millies = 0;
int deltaMillies = 2;
int flasherState = 0;

void setup() {
	pinMode(flashPin, INPUT_PULLUP);

	millies = 0;
	spaceShuttleStrip.setBrightness(255);
	spaceShuttleStrip.begin();
	spaceShuttleStrip.show(); // Initialize all pixels to 'off'
	playfieldTopStrip.setBrightness(255);
	playfieldTopStrip.begin();
	playfieldTopStrip.show(); // Initialize all pixels to 'off'
	legStrip.setBrightness(255);
	legStrip.begin();
	legStrip.show(); // Initialize all pixels to 'off'

}

void loop() {
	millies = millies + deltaMillies;
	flasherState = digitalRead(flashPin);

	if (millies == 10000)
		millies = 0;

	drawSpaceShuttleRamp();
	drawPlayfield(flasherState);
	drawLeg();
	delay(deltaMillies);
}

void drawSpaceShuttleRamp() {
	if (millies == 0 || millies == 8500) {
		spaceShuttleArea.init();
	} else if (millies < 8500) {
		spaceShuttleArea.drawShuttleLauflichtBlau(millies);
	} else {
		spaceShuttleArea.drawEinblendenRedBlue(millies);
	}
}

void drawPlayfield(int buttonState) {
	if (millies == 0) {
		playfieldTopArea.init();
	} else {
		playfieldTopArea.drawLauflichtBlauBuildingUp(millies);
	}
}

void drawLeg() {
	if (millies == 0 || millies == 7500) {
		legArea.init();
	} else if (millies < 7500) {
		// legArea.drawLauflicht(millies, 0, 0, 255);
		// legArea.drawLauflicht2(millies);
		legArea.drawEinblenden(millies);
	} else {
		legArea.drawEinblendenRedBlue(millies);
	}
}

