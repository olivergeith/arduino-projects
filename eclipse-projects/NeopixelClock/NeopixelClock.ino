// This is a demonstration on how to use an input device to trigger changes on your neo pixels.
// You should wire a momentary push button to connect from ground to a digital IO pin.  When you
// press the button it will change to a new pixel animation.  Note that you need to press the
// button once to start the first animation!

#include <Adafruit_NeoPixel.h>
#include "U8glib.h"
#include <stdarg.h>
#include <Wire.h>
#include "RTClib.h"
// Include the Bounce2 library found here :
// https://github.com/thomasfredericks/Bounce2
#include <Bounce2.h>
#include "AnimatorCircle.h"
#include "Menu.h"

// Clock DS1307
RTC_DS1307 RTC;
DateTime now;
DateTime nowOld;

#define PIXEL_PIN    6    // Digital IO pin connected to the NeoPixels.
#define PIXEL_COUNT 60
// Parameter 1 = number of pixels in strip,  neopixel stick has 8
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream, correct for neopixel stick
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip), correct for neopixel stick
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

// Oled Display
int d0 = 8;
int d1 = 9;
int res = 10;
int dc = 11;
int cs = 12;
U8GLIB_SH1106_128X64 u8g(d0, d1, cs, dc, res);

#define BUTTON_PIN_1 2
#define BUTTON_PIN_2 3
#define BUTTON_PIN_3 4
#define BUTTON_PIN_4 5
// Instantiate a Bounce object
Bounce buttonUp = Bounce();
Bounce buttonDown = Bounce();
Bounce buttonLeft = Bounce();
Bounce buttonRight = Bounce();

Menu mode;
// nummern sind wheelcolors
AnimatorCircle animatorHours(strip, 170, fullRotation);
AnimatorCircle animatorMinutes(strip, 112, fullRotation);
AnimatorCircle animatorSeconds(strip, 16, fullRotation);

void setup() {
	// Setup the first button with an internal pull-up :
	pinMode(BUTTON_PIN_1, INPUT_PULLUP);
	pinMode(BUTTON_PIN_2, INPUT_PULLUP);
	pinMode(BUTTON_PIN_3, INPUT_PULLUP);
	pinMode(BUTTON_PIN_4, INPUT_PULLUP);
	// After setting up the button, setup the Bounce instance :
	buttonUp.attach(BUTTON_PIN_1);
	buttonUp.interval(5); // interval in ms
	buttonDown.attach(BUTTON_PIN_2);
	buttonDown.interval(5); // interval in ms
	buttonLeft.attach(BUTTON_PIN_3);
	buttonLeft.interval(5); // interval in ms
	buttonRight.attach(BUTTON_PIN_4);
	buttonRight.interval(5); // interval in ms

	Wire.begin();
	RTC.begin();

	if (!RTC.isrunning()) {
		Serial.println("RTC is NOT running!");
		// following line sets the RTC to the date & time this sketch was compiled
		RTC.adjust(DateTime(__DATE__, __TIME__));
	}

	strip.setBrightness(64);
	strip.begin();
	strip.show(); // Initialize all pixels to 'off'
}

void loop() {

	// Update the Bounce instances :
	buttonUp.update();
	buttonLeft.update();
	buttonDown.update();
	buttonRight.update();

	if (buttonUp.fell() == true) {
		mode.decrement();
	}
	if (buttonDown.fell() == true) {
		mode.increment();
	}
	// sind wir im Setting Mode ?
	if (mode.getCurrentModeInt() > 0) {
		TimeSpan oneMinute(0, 0, 1, 0);
		TimeSpan oneHour(0, 1, 0, 0);
		TimeSpan oneDay(1, 0, 0, 0);
		TimeSpan oneMonth(30, 0, 0, 0);
		TimeSpan oneYear(365, 0, 0, 0);

		switch (mode.getCurrentModeInt()) {
		default:
			break;
		case 1:  // set Minutes
			if (buttonLeft.fell() == true) { // -
				RTC.adjust(now - oneMinute);
			}
			if (buttonRight.fell() == true) { // +
				RTC.adjust(now + oneMinute);
			}
			break;
		case 2: // set hours
			if (buttonLeft.fell() == true) { // -
				RTC.adjust(now - oneHour);
			}
			if (buttonRight.fell() == true) { // +
				RTC.adjust(now + oneHour);
			}
			break;
		case 3: // set day
			if (buttonLeft.fell() == true) { // -
				RTC.adjust(now - oneDay);
			}
			if (buttonRight.fell() == true) { // +
				RTC.adjust(now + oneDay);
			}
			break;
		case 4: // set month
			if (buttonLeft.fell() == true) { // -
				RTC.adjust(now - oneMonth);
			}
			if (buttonRight.fell() == true) { // +
				RTC.adjust(now + oneMonth);
			}
			break;
		case 5: // set year
			if (buttonLeft.fell() == true) { // -
				RTC.adjust(now - oneYear);
			}
			if (buttonRight.fell() == true) { // +
				RTC.adjust(now + oneYear);
			}
			break;
		case 6: // animate hours
			if (buttonLeft.fell() == true) { // -
				animatorHours.decrementAnimationStyle();
			}
			if (buttonRight.fell() == true) { // +
				animatorHours.incrementAnimationStyle();
			}
			break;
		case 7: // animate minutes
			if (buttonLeft.fell() == true) { // -
				animatorMinutes.decrementAnimationStyle();
			}
			if (buttonRight.fell() == true) { // +
				animatorMinutes.incrementAnimationStyle();
			}
			break;
		case 8: // animate Seconds
			if (buttonLeft.fell() == true) { // -
				animatorSeconds.decrementAnimationStyle();
			}
			if (buttonRight.fell() == true) { // +
				animatorSeconds.incrementAnimationStyle();
			}
			break;
		case 9: // color hours
			if (buttonLeft.read() == LOW) { // -
				animatorHours.decrementColor();
			}
			if (buttonRight.read() == LOW) { // +
				animatorHours.incrementColor();
			}
			break;
		case 10: // color minutes
			if (buttonLeft.read() == LOW) { // -
				animatorMinutes.decrementColor();
			}
			if (buttonRight.read() == LOW) { // +
				animatorMinutes.incrementColor();
			}
			break;
		case 11: // color Seconds
			if (buttonLeft.read() == LOW) { // -
				animatorSeconds.decrementColor();
			}
			if (buttonRight.read() == LOW) { // +
				animatorSeconds.incrementColor();
			}
			break;
		}
	}

	// aktuelle Uhrzeit lesen
	now = RTC.now();

	// 24h uhr auf 12h uhr umsetzen
	int hour12h = now.hour();
	if (now.hour() >= 12) {
		hour12h = hour12h - 12;
	}
	int minuteoffset = now.minute() * 5 / 60;
	int hourindex = 60 * hour12h / 12 + minuteoffset;

	strip.clear();
//	drawScala();
	animatorMinutes.draw(now.minute());
	animatorHours.draw(hourindex);
	animatorSeconds.draw(now.second());
	strip.show();

	if (nowOld.unixtime() != now.unixtime()) {
		// drawing lcd
		u8g.firstPage();
		do {
			fillLCD();
		} while (u8g.nextPage());
	}
	nowOld = now;
	delay(5);
}

void drawScala(void) {
	for (int i = 0; i < strip.numPixels(); i++) {
		if (i % 15 == 0) {
			strip.setPixelColor(i, 128, 128, 255);
		} else if (i % 5 == 0) {
			//	strip.setPixelColor(i, 16, 16, 32);
		}
	}
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
	int zeilenAbstand = 10;
// Frame
	u8g.drawRFrame(0, 0, 126, 64, 5);

	if (mode.getCurrentModeInt() > 0) { // Menümode
		u8g.setFont(u8g_font_profont12);  // select font

		u8g.drawRFrame(0, 0, 126, 15, 5);

		// Modus/Menu
		u8g.drawStr(5, 1 * zeilenAbstand, mode.getCurrentMode());
		int off = 8;
		// Zeit
		char buffer[35];  // you have to be aware of how long your data can be
		sprintf(buffer, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
		u8g.drawStr(5, off + 2 * zeilenAbstand, buffer);
		// Datum
		u8g.setFont(u8g_font_profont11);  // select font
		sprintf(buffer, "%02d.%02d.%04d", now.day(), now.month(), now.year());
		u8g.drawStr(5, off + 3 * zeilenAbstand, buffer);

		// Animation Modi
		sprintf(buffer, "Ani: %s %s %s", animatorHours.getAnimationStyleText(), animatorMinutes.getAnimationStyleText(),
				animatorSeconds.getAnimationStyleText());
		u8g.drawStr(5, off + 4 * zeilenAbstand, buffer);
		// Colors
		sprintf(buffer, "Col: %03d %03d %03d", animatorHours.getWheelColor(), animatorMinutes.getWheelColor(),
				animatorSeconds.getWheelColor());
		u8g.drawStr(5, off + 5 * zeilenAbstand, buffer);
	} else { // running Mode
		u8g.setFont(u8g_font_profont22);  // select font

		// Zeit
		char buffer[35];  // you have to be aware of how long your data can be
		sprintf(buffer, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());
		u8g.drawStr(15, 25, buffer);

		u8g.setFont(u8g_font_profont12);  // select font

		// Datum
		u8g.setFont(u8g_font_profont11);  // select font
		sprintf(buffer, "%02d.%02d.%04d", now.day(), now.month(), now.year());
		u8g.drawStr(30, 40, buffer);

		// Menu Hinweis
		u8g.drawStr(5, 58, mode.getCurrentMode());

	}
}

