// This is a demonstration on how to use an input device to trigger changes on your neo pixels.
// You should wire a momentary push button to connect from ground to a digital IO pin.  When you
// press the button it will change to a new pixel animation.  Note that you need to press the
// button once to start the first animation!

#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

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
#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif



// Oled Display
int sck__d0 = 8;    // ADA: SCK     U8G: D0   // CLK Clock
int mosi_d1 = 9;    // ADA: MOSI    U8G: D1
int res = 10;       // ADA: RES     U8G: RES
int dc = 11;        // ADA: DC      U8G: DC   // Data Command
int cs = 12;        // ADA: CS      U8G: CS   // Cable Select   
//U8GLIB_SH1106_128X64 u8g(sck__d0, mosi_d1, cs, dc, res);  
Adafruit_SSD1306 display(mosi_d1, sck__d0, dc, res, cs);



// durchlaufvariable für start-color
// wird im Loop hochgezählt
int j = 0;
int dt = 1;

// 10k Poti an pin A5
// links/rechts an Vcc und Gnd
// mitte an A5
int potiPin = A5;
int potiValue = 0;

void setup() {
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC);
  // Clear the buffer.
  display.clearDisplay();

  
  strip.setBrightness(64);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  dt = map(analogRead(potiPin), 0, 1023, 0, 45);

  for(int i=0; i< strip.numPixels(); i++) {
    strip.setPixelColor(i, Wheel(( (i * 256 / strip.numPixels()) +j) ));
  }

  strip.show();

 // Farbbeginn hochzählen
  j=j+dt;
  if (j>255){
    j=0;
  }

  // drawing lcd
  fillLCD();
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
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  
  display.drawRoundRect(0, 0, display.width(), display.height(), 8, WHITE);
  
  display.setCursor(5,8);
  display.println("Poti Rainbow");
  display.setCursor(5,24);
  display.println("Color:");
  display.setCursor(5,40);
  display.println("Speed:");
  display.setCursor(90, 24);  // set position
  display.print(j);  // 
  display.setCursor(90, 40);  // set position
  display.print(dt);  // 
  display.display();
 }




