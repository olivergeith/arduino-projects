// This is a demonstration on how to use an input device to trigger changes on your neo pixels.
// You should wire a momentary push button to connect from ground to a digital IO pin.  When you
// press the button it will change to a new pixel animation.  Note that you need to press the
// button once to start the first animation!

#include <Adafruit_NeoPixel.h>
#include "Arena.h"
#include "Monster.h"
#include "Gargoyl.h"
#include "Krieger.h"
#include "Kriegerin.h"

// Parameter 1 = number of pixels in strip,  neopixel stick has 8
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream, correct for neopixel stick
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip), correct for neopixel stick
Adafruit_NeoPixel arenaStrip = Adafruit_NeoPixel(77, 3, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel kriegerinStrip = Adafruit_NeoPixel(10, 4, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel monsterStrip = Adafruit_NeoPixel(60, 5, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel kriegerStrip = Adafruit_NeoPixel(18, 6, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel gargoylStrip = Adafruit_NeoPixel(2, 7, NEO_GRB + NEO_KHZ800);

Arena arenaArea(arenaStrip);
Kriegerin kriegerinArea(kriegerinStrip);
Monster monsterArea(monsterStrip);
Krieger kriegerArea(kriegerStrip);
Gargoyl garoylArea(gargoylStrip);

void setup() {
	arenaStrip.setBrightness(200);
	arenaStrip.begin();
	arenaStrip.show(); // Initialize all pixels to 'off'

	kriegerinStrip.setBrightness(200);
	kriegerinStrip.begin();
	kriegerinStrip.show(); // Initialize all pixels to 'off'

	monsterStrip.setBrightness(200);
	monsterStrip.begin();
	monsterStrip.show(); // Initialize all pixels to 'off'

	kriegerStrip.setBrightness(200);
	kriegerStrip.begin();
	kriegerStrip.show(); // Initialize all pixels to 'off'

	gargoylStrip.setBrightness(200);
	gargoylStrip.begin();
	gargoylStrip.show(); // Initialize all pixels to 'off'

}

void loop() {
	arenaArea.draw();
	kriegerinArea.draw();
	monsterArea.draw();
	kriegerArea.draw();
	garoylArea.draw();

	arenaStrip.show();
	kriegerinStrip.show();
	monsterStrip.show();
	kriegerStrip.show();
	gargoylStrip.show();
	delay(25);
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
	WheelPos = 255 - WheelPos;
	if (WheelPos < 85) {
		return arenaStrip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
	}
	if (WheelPos < 170) {
		WheelPos -= 85;
		return arenaStrip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
	}
	WheelPos -= 170;
	return arenaStrip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

