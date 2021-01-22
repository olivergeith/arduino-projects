// A basic everyday NeoPixel strip test program.

// NEOPIXEL BEST PRACTICES for most reliable operation:
// - Add 1000 uF CAPACITOR between NeoPixel strip's + and - connections.
// - MINIMIZE WIRING LENGTH between microcontroller board and first pixel.
// - NeoPixel strip's DATA-IN should pass through a 300-500 OHM RESISTOR.
// - AVOID connecting NeoPixels on a LIVE CIRCUIT. If you must, ALWAYS
//   connect GROUND (-) first, then +, then data.
// - When using a 3.3V microcontroller with a 5V-powered NeoPixel strip,
//   a LOGIC-LEVEL CONVERTER on the data line is STRONGLY RECOMMENDED.
// (Skipping these may work OK on your workbench but can fail in the field)

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    13

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 12

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)


// setup() function -- runs once at startup --------------------------------

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
}


// loop() function -- runs repeatedly as long as board is on ---------------

void loop() {
  // Fill along the length of the strip in various colors...
  //colorWipe(strip.Color(255,   0,   0), 50); // Red
  //colorWipe(strip.Color(  255,   255, 0), 50); // YELLOW

  // Do a theater marquee effect in various colors...
  //theaterChase(strip.Color(127, 127, 127), 50); // White, half brightness
  //theaterChase(strip.Color(127,   0,   0), 50); // Red, half brightness
  //theaterChase(strip.Color(  0,   0, 127), 50); // Blue, half brightness

//  rainbow(10);             // Flowing rainbow cycle along the whole strip
  //theaterChaseRainbow(50); // Rainbow-enhanced theaterChase variant

for (int i=0; i<10; i++){
  if (i ==0){ 
    drawRandomColors2(100);
    drawRotatingColors(50);
  }
  drawLauflichtBlauBuildingUp2(10+random(80));
  drawTronLight(100);
  
  if (i ==1){ 
//    drawRotatingColors(50);
  }
}

//  drawLauflichtBlauBuildingUp2(50);
//  drawLauflichtBlauBuildingUp2(100);
//  drawLauflichtBlauBuildingUp2(200);
/*  
  drawRandomColors2(100);
  drawRandomTronLight(100);
  drawTronLight(100);
//  drawRotatingColors(50);
  colorWipe(strip.Color(  0, 255,   0), 400); // Green
  */
}


// Some functions of our own for creating animated effects -----------------

// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, 0,0,0);         //  Set pixel's color (in RAM)
  }
  strip.show();                          //  Update strip to match
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
  delay(5000);                           //  Pause for a moment
}

// Theater-marquee-style chasing lights. Pass in a color (32-bit value,
// a la strip.Color(r,g,b) as mentioned above), and a delay time (in ms)
// between frames.
void theaterChase(uint32_t color, int wait) {
  for(int a=0; a<10; a++) {  // Repeat 10 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
  }
}

// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) {
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}

// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void drawRandomColors(int wait) {
    for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
      strip.setPixelColor(i, getRandomColor(255));
    }
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
}

void drawRandomColors2(int wait) {
    for(int c=0; c<100; c++) { // For each pixel in strip...
      int pix1 = random(strip.numPixels());
      int pix2 = random(strip.numPixels());
      int pix3 = random(strip.numPixels());
      uint32_t col = getRandomColor(255);
      for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
        if (i == pix1 || i == pix2 || i == pix3){
          strip.setPixelColor(i, getRandomColor(255));
        }else{
          strip.setPixelColor(i, 0,0,0);
        }
      }
      strip.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
}


// Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for(int a=0; a<30; a++) {  // Repeat 30 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show();                // Update strip with new contents
      delay(wait);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
}
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

uint32_t getColorRotGelbGruen(int color) {
  switch (color) {
  default:
  case 0:
    return Wheel(0);
  case 1:
    return Wheel(16);
  case 2:
    return Wheel(64);

  }
}

uint32_t getColorRed(int brightness) {
  return strip.Color(brightness, 0, 0);
}

uint32_t getColorBlue(int brightness) {
  return strip.Color(0, 0, brightness);
}

uint32_t getColorWhite(int brightness) {
  return strip.Color(brightness, brightness, brightness);
}

uint32_t getRandomColor(int brightness) {
  return Wheel(random(256));
}

uint32_t getColorGreen(int brightness) {
  return strip.Color(0, brightness, 0);
}



void drawTronLight(int wait) {
  int animationStep =0;
  boolean animating = false;
  int lauflichtStep =0;
    
    for(int c=0; c<96; c++) { // loop 100x
  
      if (animating)
        animationStep++;
      else
        animationStep--;
    
      if (animationStep >= strip.numPixels()-1)
        animating = false;
      if (animationStep <= 0){
        animating = true;
      }
      for (int i = 0; i < strip.numPixels(); i++) {
        if (i == animationStep)
          strip.setPixelColor(i, getColorRed(255));
        else if (i == animationStep + 1 || i == animationStep - 1)
          strip.setPixelColor(i, getColorRed(128));
        else if (i == animationStep + 2 || i == animationStep - 2)
          strip.setPixelColor(i, getColorRed(48));
    //    else if (i == animationStep + 3 || i == animationStep - 3)
    //      strip.setPixelColor(i, getColorRed(16));
        else
          strip.setPixelColor(i, 0, 0, 0);
      }
      strip.show();
      delay (wait);
    }
}

void drawRandomTronLight(int wait) {
  int animationStep =0;
  boolean animating = false;
  int lauflichtStep =0;

  int rand = random(256);
  uint32_t col = Wheel(rand);


    
    for(int c=0; c<100; c++) { // loop 100x
      rand = rand +8;
      if (rand >255)
        rand = 0;  
      if (animating)
        animationStep++;
      else
        animationStep--;
    
      if (animationStep >= strip.numPixels()-1)
        animating = false;
      if (animationStep <= 0)
        animating = true;
      
      for (int i = 0; i < strip.numPixels(); i++) {
        if (i == animationStep)
          strip.setPixelColor(i, Wheel(rand));
        else
          strip.setPixelColor(i, 0, 0, 0);
      }
      strip.show();
      delay (wait);
    }
}


void drawRotatingColors(int wait) {
  int animationStep =0;
  boolean animating = false;
  int lauflichtStep =0;
    for(int c=0; c<200; c++) { // loop 100x
      animationStep = animationStep + 4;
      if (animationStep >= 256)
        animationStep = 0;
      for (int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, Wheel(animationStep + i * 256 / strip.numPixels() ));
      }
      strip.show();
      delay (wait);
    }
}

void drawLauflichtBlauBuildingUp(int wait) {
  uint32_t col1 = getRandomColor(255);
  uint32_t col2 = getRandomColor(255);
  int animationStep =0;
  int max = strip.numPixels();
  for(int c=0; c<200; c++) { // loop 100x
    animationStep++;
    if (animationStep == max) {
      animationStep = 0;
      max--;
      if (max == 0){
        max = strip.numPixels();
        delay(1000);
        col1 = getRandomColor(255);
        col2 = getRandomColor(255);
      }
    }
    for (int i = 0; i < max; i++) {
      if (i == animationStep) {
        strip.setPixelColor(i, col1);
      } else {
        strip.setPixelColor(i, 0, 0, 0);
      }
    }
    for (int i = max; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, col2);
    }
    strip.show();
    delay (wait);
  }
}

void drawLauflichtBlauBuildingUp2(int wait) {
  uint32_t col1 = getRandomColor(255);
  uint32_t col2 = getRandomColor(255);
  int animationStep =0;
  int max = strip.numPixels();
  while(max >0){
    animationStep++;
    if (animationStep == max) {
      animationStep = 0;
      max--;
    }
    for (int i = 0; i < max; i++) {
      if (i == animationStep) {
        strip.setPixelColor(i, col1);
      } else {
        strip.setPixelColor(i, 0, 0, 0);
      }
    }
    for (int i = max; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, col2);
    }
    strip.show();
    if (max == 0){
       delay(1000);
    }
    delay (wait);
  }
}



  
