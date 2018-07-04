/*
 LED VU meter for Arduino and Adafruit NeoPixel LEDs.

 Hardware requirements:
 - Most Arduino or Arduino-compatible boards (ATmega 328P or better).
 - Adafruit Electret Microphone Amplifier (ID: 1063)
 - Adafruit Flora RGB Smart Pixels (ID: 1260)
 OR
 - Adafruit NeoPixel Digital LED strip (ID: 1138)
 - Optional: battery for portable use (else power through USB or adapter)
 Software requirements:
 - Adafruit NeoPixel library

 Connections:
 - 3.3V to mic amp +
 - GND to mic amp -
 - Analog pin to microphone output (configurable below)
 - Digital pin to LED data input (configurable below)
 See notes in setup() regarding 5V vs. 3.3V boards - there may be an
 extra connection to make and one line of code to enable or disable.

 Written by Adafruit Industries.  Distributed under the BSD license.
 This paragraph must be included in any redistribution.
 */

#include <Adafruit_NeoPixel.h>

#define N_PIXELS  60  // Number of pixels in strand
#define MIC_PIN   A4  // Microphone is attached to this analog pin
#define LED_PIN    6  // NeoPixel LED strand is connected to this pin
#define DC_OFFSET  0  // DC offset in mic signal - if unusure, leave 0
#define NOISE     10  // Noise/hum/interference in mic signal
#define SAMPLES   50  // Length of buffer for dynamic level adjustment
#define TOP       20 // Allow dot to go slightly off scale
#define SAMPLING  2  // Rate of peak falling dot

byte peak = 0,      // Used for falling dot
		dotCount = 0,      // Frame counter for delaying dot-falling speed
		volCount = 0;      // Frame counter for storing past volume data
int vol[SAMPLES],       // Collection of prior volume samples
		lvl = 10,      // Current "dampened" audio level
		minLvlAvg = 0,      // For dynamic adjustment of graph low & high
		maxLvlAvg = 512;
Adafruit_NeoPixel nasaStrip = Adafruit_NeoPixel(N_PIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);
int pixelColors[N_PIXELS];       // Collection of all PixelColors (Wheelcolors)

float rainbow = 0;

void setup() {
	memset(vol, 0, sizeof(vol));
	nasaStrip.begin();
	Serial.begin(9600);
	nasaStrip.setBrightness(64);
}

int readAnalog() {
	int n1 = analogRead(MIC_PIN);
	return n1;
}

void loop() {
	uint8_t i;
	uint16_t minLvl, maxLvl;
	int n, height;

	n = readAnalog();
	Serial.println(n);
	n = abs(n - 512 - DC_OFFSET); // Center on zero

	n = (n <= NOISE) ? 0 : (n - NOISE);             // Remove noise/hum
	lvl = ((lvl * 7) + n) >> 3;    // "Dampened" reading (else looks twitchy)

	// Calculate bar height based on dynamic min/max levels (fixed point):
	height = TOP * (lvl - minLvlAvg) / (long) (maxLvlAvg - minLvlAvg);

	if (height < 0L)
		height = 0;      // Clip output
	else if (height > TOP)
		height = TOP;
	if (height > peak)
		peak = height; // Keep 'peak' dot at top

	int color = map(height, 0, TOP, 0, 255);
//	Serial.println(height);

	if (dotCount == SAMPLING) {
		rainbow += 0.2;
		if (rainbow > 255) {
			rainbow = 0;
		}
		color = color + rainbow;
		if (color > 255)
			color = color - 255;
		putNewColorValue(color);
		fillStripe();
		//fillStripeColorfull();
		nasaStrip.show(); // Update strip
		dotCount = 0;
	}
	dotCount++;

	vol[volCount] = n;                      // Save sample for dynamic leveling
	if (++volCount >= SAMPLES)
		volCount = 0; // Advance/rollover sample counter

	// Get volume range of prior frames
	minLvl = maxLvl = vol[0];
	for (i = 1; i < SAMPLES; i++) {
		if (vol[i] < minLvl)
			minLvl = vol[i];
		else if (vol[i] > maxLvl)
			maxLvl = vol[i];
	}
	// minLvl and maxLvl indicate the volume range over prior frames, used
	// for vertically scaling the output graph (so it looks interesting
	// regardless of volume level).  If they're too close together though
	// (e.g. at very low volume levels) the graph becomes super coarse
	// and 'jumpy'...so keep some minimum distance between them (this
	// also lets the graph go to zero when no sound is playing):
	if ((maxLvl - minLvl) < TOP)
		maxLvl = minLvl + TOP;
	minLvlAvg = (minLvlAvg * 60 + minLvl) >> 6; // Dampen min/max levels
	maxLvlAvg = (maxLvlAvg * 60 + maxLvl) >> 6; // (fake rolling average)
}

// Input a value 0 to 255 to get a color value.
// The colors are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
	if (WheelPos < 85) {
		return nasaStrip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
	} else if (WheelPos < 170) {
		WheelPos -= 85;
		return nasaStrip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
	} else {
		WheelPos -= 170;
		return nasaStrip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
	}
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel2(byte WheelPos) {
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

void putNewColorValue(int col) {
	for (int i = N_PIXELS - 1; i > 0; i--) {
		pixelColors[i] = pixelColors[i - 1];
	}
	pixelColors[0] = col;
}

void fillStripe() {
	for (int i = 0; i < N_PIXELS; i++) {
		if (pixelColors[i] == 0)
			nasaStrip.setPixelColor(i, 0, 0, 0);
		else
			nasaStrip.setPixelColor(i, Wheel2(pixelColors[i]));
	}
}

void fillStripeColorfull() {
	for (int i = 0; i < N_PIXELS; i++) {
		nasaStrip.setPixelColor(i, Wheel2(pixelColors[i]));
	}
}

