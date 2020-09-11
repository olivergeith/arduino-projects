// This is a demonstration on how to use an input device to trigger changes on your neo pixels.
// You should wire a momentary push button to connect from ground to a digital IO pin.  When you
// press the button it will change to a new pixel animation.  Note that you need to press the
// button once to start the first animation!

#include <Adafruit_NeoPixel.h>

#include "LegLight8.h"
#include <Bounce2.h>

#define BUTTON_PIN 4

// Parameter 1 = number of pixels in strip,  neopixel stick has 8
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream, correct for neopixel stick
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip), correct for neopixel stick

Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(16, 7, NEO_GRB + NEO_KHZ800);
LegLight8 circle(strip1);

int millies = 0;
int deltaMillies = 25;
int modus = 0;

Bounce button = Bounce();

void setup() {

	millies = 0;

	// Setup the first button with an internal pull-up :
	// Button schließt gegen Masse
	pinMode(BUTTON_PIN, INPUT_PULLUP);
	button.attach(BUTTON_PIN);
	button.interval(5); // interval in ms

	strip1.begin();
	strip1.setBrightness(255);
	strip1.show(); // Initialize all pixels to 'off'
}

void loop() {

	button.update();
	if (button.fell() == true) {
		incrementMode();
	}

	millies = millies + deltaMillies;

	if (millies >= 10000)
		millies = 0;

	draw();
	delay(deltaMillies);
}
void draw() {
	switch (modus) {
	default:
	case 0:
		circle.drawRotatingColors(1);
		break;
	case 1:
		circle.drawRotatingColors(4);
		break;
	case 2:
		circle.drawRotatingColors(8);
		break;
	case 3:
		circle.drawRotatingColors(16);
		break;
	case 4:
		circle.drawChangingColor(millies, 1);
		break;
	case 5:
		circle.drawDoubleLauflichtWheeled(millies);
		break;
	case 6:
		circle.drawLauflichtWheeled(millies);
		break;
	case 7:
		circle.drawRandomSegment(millies, 150);
		break;
	case 8:
		circle.drawRandomSegment(millies, 100);
		break;
	case 9:
		circle.drawRandomSegment(millies, 50);
		break;
	case 10:
		circle.drawRandomSegment(millies, 25);
		break;
	case 11:
		circle.drawPoliceLight(millies);
		break;
	}

}

void incrementMode() {
	modus++;
	if (modus > 11) {
		modus = 0;
	}
	if (modus >= 3) {
		circle.init();
	}
}

