// This is a demonstration on how to use an input device to trigger changes on your neo pixels.
// You should wire a momentary push button to connect from ground to a digital IO pin.  When you
// press the button it will change to a new pixel animation.  Note that you need to press the
// button once to start the first animation!

#include <Adafruit_NeoPixel.h>
#include "U8glib.h"
#include "IRremote.h"


#define PIXEL_PIN    6    // Digital IO pin connected to the NeoPixels.
#define PIXEL_COUNT 16
// Parameter 1 = number of pixels in strip,  neopixel stick has 8
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream, correct for neopixel stick
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip), correct for neopixel stick
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN,
NEO_GRB + NEO_KHZ800);

// IRReceiver
int IR_RECV_PIN = 7;
IRrecv irrecv(IR_RECV_PIN);
decode_results results;
String ircode="";

// Oled Display
int d0 = 8;
int d1 = 9;
int res = 10;
int dc = 11;
int cs = 12;
U8GLIB_SH1106_128X64 u8g(d0, d1, cs, dc, res);

// durchlaufvariable f�r start-color
// wird im Loop hochgez�hlt
int j = 0;
int dt = 1;		// Speed
int cycles = 1; // Anzahl der Farbdurchl�ufe


void setup() {
	Serial.begin(9600);
	irrecv.enableIRIn();
	strip.setBrightness(64);
	strip.begin();
	strip.show(); // Initialize all pixels to 'off'
}

void loop() {

	ircode = "";
	if (irrecv.decode(&results)) {
		Serial.print(results.decode_type);
		Serial.print(" - ");
		Serial.println(results.value, DEC);
		switch (results.value) {
		default:
			break;
		case 16754775: // dt +
			dt = dt*2;
			if (dt > 64)
				dt = 64;
			ircode = "speed ++";
			break;
		case 16769055: // dt -
			dt=dt/2;
			if (dt < 1)
				dt = 1;
			ircode = "speed --";
			break;
		case 16720605: // cycles--
			cycles--;
			if (cycles < 1)
				cycles = 1;
			ircode = "cycle --";
			break;
		case 16712445: // cycles++
			cycles++;
			if (cycles > 16)
				cycles = 16;
			ircode = "cycle ++";
			break;
		}
		irrecv.resume();
	}

	for (int i = 0; i < strip.numPixels(); i++) {
		strip.setPixelColor(i,
				Wheel(((i * 256 / strip.numPixels() * cycles) + j)));
	}
	/*
	 for(int i=0; i< strip.numPixels(); i++) {
	 if(i<leds)
	 strip.setPixelColor(i, Wheel(( (i * 256 / leds) +j) ));
	 else
	 strip.setPixelColor(i, 0,0,0);
	 }
	 */
	strip.show();

	// Farbbeginn hochz�hlen
	j = j + dt;
	if (j > 255) {
		j = 0;
	}

	// drawing lcd
	u8g.firstPage();
	do {
		fillLCD();
	} while (u8g.nextPage());

	delay(20);
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
	WheelPos = 255 - WheelPos;
	if (WheelPos < 85) {
		return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
	}
	if (WheelPos < 170) {
		WheelPos -= 85;
		return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
	}
	WheelPos -= 170;
	return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void fillLCD(void) {
//  u8g.setFont(u8g_font_unifont);  // select font
	u8g.setFont(u8g_font_profont11);  // select font
	int zeilenAbstand = 11;
	u8g.drawRFrame(0, 0, 126, 64, 5);
	u8g.drawStr(5, 1 * zeilenAbstand, "Poti Rainbow");
	u8g.drawStr(5, 2 * zeilenAbstand, "Color:");
	u8g.drawStr(5, 3 * zeilenAbstand, "Speed:");
	u8g.drawStr(5, 4 * zeilenAbstand, "Cycles:");
	u8g.drawStr(5, 5 * zeilenAbstand, "IRCode:");
	u8g.setPrintPos(90, 2 * zeilenAbstand);  // set position
	u8g.print(j);  //
	u8g.setPrintPos(90, 3 * zeilenAbstand);  // set position
	u8g.print(dt);  //
	u8g.setPrintPos(90, 4 * zeilenAbstand);  // set position
	u8g.print(cycles);  //
	u8g.setPrintPos(50, 5 * zeilenAbstand);  // set position
	u8g.print(ircode);  //
	u8g.setPrintPos(100, 5 * zeilenAbstand);  // set position
	u8g.print(results.decode_type);  //
}

