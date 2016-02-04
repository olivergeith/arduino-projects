// This is a demonstration on how to use an input device to trigger changes on your neo pixels.
// You should wire a momentary push button to connect from ground to a digital IO pin.  When you
// press the button it will change to a new pixel animation.  Note that you need to press the
// button once to start the first animation!

#include <Adafruit_NeoPixel.h>
#include "U8glib.h"

#define BUTTON_PIN   2    // Digital IO pin connected to the button.  This will be
                          // driven with a pull-up resistor so the switch should
                          // pull the pin to ground momentarily.  On a high -> low
                          // transition the button press logic will execute.

#define PIXEL_PIN    6    // Digital IO pin connected to the NeoPixels.

#define PIXEL_COUNT 16

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



bool oldState = HIGH;
int dt = 1;
int j = 0;
void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  strip.setBrightness(64);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // Get current button state.
  bool newState = digitalRead(BUTTON_PIN);
  // Check if state changed from high to low (button press).
  if (newState == LOW && oldState == HIGH) {
    // Short delay to debounce button.
    delay(20);
    // Check if button is still low after debounce.
    newState = digitalRead(BUTTON_PIN);
    if (newState == LOW) {
      dt = dt * 2;
      if (dt > 64)
        dt = 1;
    }
  }

  for(int i=0; i< strip.numPixels(); i++) {
    strip.setPixelColor(i, Wheel(( (i * 256 / strip.numPixels())  + j) ));
  }
  strip.show();

  // Farbbeginn hochzählen
  j=j+dt;
  if (j>255){
    j=0;
  }

  // drawing lcd
  u8g.firstPage();  
  do {
    fillLCD();
  } while( u8g.nextPage() );

  // Set the last button state to the old state.
  oldState = newState;
  delay(20);
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}


void fillLCD(void){
  u8g.setFont(u8g_font_unifont);  // select font
  u8g.drawFrame(0,0,126,64);
  u8g.drawStr(5, 16, "Color Rainbow");
  u8g.drawStr(5, 36, "Color:");
  u8g.drawStr(5, 52, "Speed:");
  u8g.setPrintPos(90, 36);  // set position
  u8g.print(j);  // 
  u8g.setPrintPos(90, 52);  // set position
  u8g.print(dt);  // 
 }




