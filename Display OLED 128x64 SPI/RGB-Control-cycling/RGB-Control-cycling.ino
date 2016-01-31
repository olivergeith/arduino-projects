#include "U8glib.h"

// Oled Display
int d0 = 8;
int d1 = 9;
int res = 10;
int dc = 11;
int cs = 12;
U8GLIB_SH1106_128X64 u8g(d0, d1, cs, dc, res);  

// RGB LED mit common athode (-)
// der Längste Pin ist minus
// blau/grün/minus/rot

int redLEDPin = 6;
int greenLEDPin = 5;
int blueLEDPin = 3;

// Drei Taster gegen Masse
int redSwitchPin = 7;
int greenSwitchPin = 4;
int blueSwitchPin = 2;

// maxcolor value
int maxColor = 50;

// die Farbwerte
int red = 0;
int blue = maxColor/2;
int green = maxColor;

// inkremente 
int dred = 2;
int dblue = 2;
int dgreen = 2;
// faktoren 
int fred = 1;
int fblue = 1;
int fgreen = 1;
 


void draw(void){
  int posX = 60;
  u8g.setFont(u8g_font_unifont);  // select font
 // u8g.setFont(u8g_font_helvB12);  // select font

  u8g.drawFrame(0,0,126,64);
  u8g.drawStr(5, 16, "Rot  :");
  u8g.drawStr(5, 32, "Gruen:");
  u8g.drawStr(5, 48, "Blau :");

  u8g.setPrintPos(posX, 16);  // set position
  u8g.print(red);  // 
  u8g.setPrintPos(posX, 32);  // set position
  u8g.print(green);  // 
  u8g.setPrintPos(posX, 48);  // set position
  u8g.print(blue);  // 

  posX = 100;
  u8g.setPrintPos(posX, 16);  // set position
  u8g.print(dred);  // 
  u8g.setPrintPos(posX, 32);  // set position
  u8g.print(dgreen);  // 
  u8g.setPrintPos(posX, 48);  // set position
  u8g.print(dblue);  // 


  
 }




void setup(void) {
  pinMode(redLEDPin, OUTPUT);
  pinMode(greenLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);  

  pinMode(redSwitchPin, INPUT_PULLUP);
  pinMode(greenSwitchPin, INPUT_PULLUP);
  pinMode(blueSwitchPin, INPUT_PULLUP);

}


void calcColors(void){
    red = red + dred*fred;
  if (red > maxColor) {
    red = maxColor;
    fred = -1;
  }else if (red <0){
    red = 0;
    fred = 1;
  }
  green = green + dgreen*fgreen;
  if (green > maxColor) {
    green = maxColor;
    fgreen = -1;
  }else if (green <0){
    green = 0;
    fgreen = 1;
  }
  blue = blue + dblue*fblue;
  if (blue > maxColor) {
    blue = maxColor;
    fblue = -1;
  }else if (blue <0){
    blue = 0;
    fblue = 1;
  }

}
void calcColors2(void){
  red = red + dred*fred;
  if (red > maxColor) {
    red = 0;
  }
  green = green + dgreen*fgreen;
  if (green > maxColor) {
    green = 0;
  }
  blue = blue + dblue*fblue;
  if (blue > maxColor) {
    blue = 0;
  }
}



void loop(void) {
  if (digitalRead(redSwitchPin) == LOW)
  {
    dred++;
    if (dred > 10) dred = 0;
  }
  if (digitalRead(greenSwitchPin) == LOW)
  {
    dgreen++;
    if (dgreen > 10) dgreen = 0;
  }
  if (digitalRead(blueSwitchPin) == LOW)
  {
    dblue++;
    if (dblue > 10) dblue = 0;
  }

  // incrementing the colors

  calcColors2();
  
  analogWrite(redLEDPin, red);
  analogWrite(greenLEDPin, green);
  analogWrite(blueLEDPin, blue);  
 
  u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );
  
  delay(10); 
}
