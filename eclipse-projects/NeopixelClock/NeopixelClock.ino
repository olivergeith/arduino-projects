// This is a demonstration on how to use an input device to trigger changes on your neo pixels.
// You should wire a momentary push button to connect from ground to a digital IO pin.  When you
// press the button it will change to a new pixel animation.  Note that you need to press the
// button once to start the first animation!

#include <Adafruit_NeoPixel.h>
#include "U8glib.h"

#include <Wire.h>
#include "RTClib.h"

// Clock DS1307
RTC_DS1307 RTC;
DateTime now;

#define PIXEL_PIN    6    // Digital IO pin connected to the NeoPixels.
#define PIXEL_COUNT 60
// Parameter 1 = number of pixels in strip,  neopixel stick has 8
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream, correct for neopixel stick
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip), correct for neopixel stick
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN,
		NEO_GRB + NEO_KHZ800);

// Oled Display
int d0 = 8;
int d1 = 9;
int res = 10;
int dc = 11;
int cs = 12;
U8GLIB_SH1106_128X64 u8g(d0, d1, cs, dc, res);

void setup() {
	Serial.begin(9600);
	Wire.begin();
	RTC.begin();

	if (!RTC.isrunning()) {
		Serial.println("RTC is NOT running!");
		// following line sets the RTC to the date & time this sketch was compiled
		//RTC.adjust(DateTime(__DATE__, __TIME__));
	}

	strip.setBrightness(64);
	strip.begin();
	strip.show(); // Initialize all pixels to 'off'
}

void loop() {
	now = RTC.now();

	Serial.print(now.year(), DEC);
	Serial.print('/');
	Serial.print(now.month(), DEC);
	Serial.print('/');
	Serial.print(now.day(), DEC);
	Serial.print(' ');
	Serial.print(now.hour(), DEC);
	Serial.print(':');
	Serial.print(now.minute(), DEC);
	Serial.print(':');
	Serial.print(now.second(), DEC);
	Serial.println();

	// 24h uhr auf 12h uhr umsetzen
	int hour12h = now.hour();
	if (now.hour() >= 12) {
		hour12h = hour12h - 12;
	}
	int minuteoffset = now.minute() * 5 / 60;
	int hourindex = 60 * hour12h / 12 + minuteoffset;

	// erstmal schwarz/aus
	strip.clear();
//	for (int i = 0; i < strip.numPixels(); i++) {
//		strip.setPixelColor(i, 0, 0, 0);
//	}

	strip.setPixelColor(now.minute(), 255, 0, 0);
	strip.setPixelColor(hourindex, 255, 255, 255);
	// breitere Stunden
	if (hourindex == strip.numPixels()) {
		strip.setPixelColor(hourindex - 1, 0, 0, 255);
		strip.setPixelColor(0, 0, 0, 255);
	} else if (hourindex == 0) {
		strip.setPixelColor(hourindex + 1, 0, 0, 255);
		strip.setPixelColor(strip.numPixels() - 1, 0, 0, 255);
	} else {
		strip.setPixelColor(hourindex + 1, 0, 0, 255);
		strip.setPixelColor(hourindex - 1, 0, 0, 255);
	}
	strip.setPixelColor(now.second(), 255, 255, 0);
	strip.show();

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
	u8g.setFont(u8g_font_profont11);  // select font
	int zeilenAbstand = 11;
	u8g.drawRFrame(0, 0, 126, 64, 5);
	u8g.drawStr(5, 1 * zeilenAbstand, "Clock");
	u8g.drawStr(5, 2 * zeilenAbstand, "Uhr:");
	u8g.setPrintPos(50, 2 * zeilenAbstand);  // set position
	u8g.print(now.hour());  //
	u8g.setPrintPos(70, 2 * zeilenAbstand);  // set position
	u8g.print(now.minute());  //
	u8g.setPrintPos(90, 2 * zeilenAbstand);  // set position
	u8g.print(now.second());  //
}

