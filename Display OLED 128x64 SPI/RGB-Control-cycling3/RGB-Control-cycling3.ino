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
int blue = 0;
int green = 0;


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
//  u8g.setPrintPos(posX, 16);  // set position
//  u8g.print(dred);  // 
//  u8g.setPrintPos(posX, 32);  // set position
//  u8g.print(dgreen);  // 
//  u8g.setPrintPos(posX, 48);  // set position
//  u8g.print(dblue);  // 


  
 }




void setup(void) {
  pinMode(redLEDPin, OUTPUT);
  pinMode(greenLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);  

  pinMode(redSwitchPin, INPUT_PULLUP);
  pinMode(greenSwitchPin, INPUT_PULLUP);
  pinMode(blueSwitchPin, INPUT_PULLUP);

}



int state = 1;
void calcColors3(void){
  red = random(255);
  blue = random(255);
  green = random(255);
}





void loop(void) {

  calcColors3();
  
  analogWrite(redLEDPin, red);
  analogWrite(greenLEDPin, green);
  analogWrite(blueLEDPin, blue);  
 
  u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );
  
  delay(100); 
}
