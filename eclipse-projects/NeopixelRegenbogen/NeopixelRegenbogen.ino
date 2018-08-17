// This is a demonstration on how to use an input device to trigger changes on your neo pixels.
// You should wire a momentary push button to connect from ground to a digital IO pin.  When you
// press the button it will change to a new pixel animation.  Note that you need to press the
// button once to start the first animation!

#include <Adafruit_NeoPixel.h>

#define PIXEL_PIN    7    // Digital IO pin connected to the NeoPixels.
#define PIXEL_COUNT 11
// Parameter 1 = number of pixels in strip,  neopixel stick has 8
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream, correct for neopixel stick
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip), correct for neopixel stick
Adafruit_NeoPixel nasaStrip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

// durchlaufvariable für start-color
// wird im Loop hochgezählt
int j = 0;
int dt = 1;		// Speed
int cycles = 2; // Anzahl der Farbdurchläufe

void setup() {
//  u8g.setRot180();
	nasaStrip.setBrightness(64);
	nasaStrip.begin();
	nasaStrip.show(); // Initialize all pixels to 'off'
}

void colorWheel() {
	dt = 5;
	cycles = 1;
	for (int i = 0; i < nasaStrip.numPixels(); i++) {
		nasaStrip.setPixelColor(i, Wheel(((i * 256 / nasaStrip.numPixels() * cycles) + j)));
	}
	nasaStrip.show();
	// Farbbeginn hochzählen
	j = j + dt;
	if (j > 255) {
		j = 0;
	}
	delay(10);
}

void colorWheelMitBlitz() {
	dt = 16;
	cycles = 1;
	int rand = random(nasaStrip.numPixels());
	for (int i = 0; i < nasaStrip.numPixels(); i++) {
		nasaStrip.setPixelColor(i, Wheel(((i * 256 / nasaStrip.numPixels() * cycles) + j)));
		if (i == rand)
			nasaStrip.setPixelColor(i, 255, 255, 255);
	}
	nasaStrip.show();
	// Farbbeginn hochzählen
	j = j + dt;
	if (j > 255) {
		j = 0;
	}
	delay(50);
}

int runde = 0;
void lauflicht() {
	for (int i = 0; i < nasaStrip.numPixels(); i++) {
		if (i == j) {
			nasaStrip.setPixelColor(i, Wheel(runde));
//			nasaStrip.setPixelColor(i, 0, 0, 255);
		} else if (i == nasaStrip.numPixels() - j) {
			nasaStrip.setPixelColor(i, Wheel(runde + 128));
			//nasaStrip.setPixelColor(i, 255, 255, 255);
		} else {
			nasaStrip.setPixelColor(i, 0, 0, 0);
		}
	}
	nasaStrip.show();
	// Farbbeginn hochzählen
	j = j + 1;
	if (j == nasaStrip.numPixels()) {
		j = 0;
		runde = runde + 8;
		if (runde >= 256)
			runde = 0;
	}
	delay(25);
}

void loop() {
	colorWheelMitBlitz();
	//lauflicht();
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
	WheelPos = 255 - WheelPos;
	if (WheelPos < 85) {
		return nasaStrip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
	}
	if (WheelPos < 170) {
		WheelPos -= 85;
		return nasaStrip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
	}
	WheelPos -= 170;
	return nasaStrip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

