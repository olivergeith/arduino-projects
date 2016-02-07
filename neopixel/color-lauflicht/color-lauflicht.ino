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


// durchlaufvariable für start-color
// wird im Loop hochgezählt

// 10k Poti an pin A5
// links/rechts an Vcc und Gnd
// mitte an A5
int potiPinSpeed = A5;
int potiPinColor = A4;

void setup() {
//  u8g.setRot180();
  strip.setBrightness(64);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

int aktivLED = 0;
int speedy = 100;
int neocol = 0;

void loop() {
  speedy = map(analogRead(potiPinSpeed), 0, 1023, 0, 500);
  neocol = map(analogRead(potiPinColor), 0, 1023, 0, 255);
  for(int i=0; i< strip.numPixels(); i++) {
    if (i <= aktivLED){
      strip.setPixelColor(i, Wheel(neocol));
    }else{
      int col = random(255);
      strip.setPixelColor(i, Wheel(col));
    }
  }
//  strip.setPixelColor(aktivLED, 255,255,255);
  strip.show();

  // drawing lcd
  u8g.firstPage();  
  do {
    fillLCD();
  } while( u8g.nextPage() );

  aktivLED++;
  if (aktivLED >=strip.numPixels()){
    delay(1000);
    aktivLED = 0;
  }
  delay(speedy);
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
//  u8g.setFont(u8g_font_unifont);  // select font
  u8g.setFont(u8g_font_profont11);  // select font
  int zeilenAbstand = 12;
  u8g.drawFrame(0,0,126,64);
  u8g.drawStr(5, 1*zeilenAbstand, "Poti Rainbow");
  u8g.drawStr(5, 2*zeilenAbstand, "Color:");
  u8g.drawStr(5, 3*zeilenAbstand, "Speed:");
  u8g.setPrintPos(90, 2*zeilenAbstand);  // set position
  u8g.print(neocol);  // 
  u8g.setPrintPos(90, 3*zeilenAbstand);  // set position
  u8g.print(speedy);  // 
 }




