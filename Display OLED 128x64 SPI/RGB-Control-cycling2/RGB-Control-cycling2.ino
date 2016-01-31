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

// inkremente 
int dred = 2;
int dblue = 2;
int dgreen = 2;
int dall = 1; 


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



int state = 1;
void calcColors3(void){
  if (state == 1)
  {
    red = red + dall;
    if (red > maxColor) {
      red = maxColor;
      state = 2;
    }
    green = 0;
    blue = 0;
  }
  if (state == 2)
  {
    red = maxColor;
    green = green + dall;
    if (green > maxColor) {
      green = maxColor;
      state = 3;
    }
    blue = blue - dall;
    if (blue < 0) {
      blue = 0;
    }
  }
  if (state == 3)
  {
    red = red - dall;
    if (red < 0) {
      red = 0;
    }
    green = maxColor;
    blue = blue + dall;
    if (blue > maxColor) {
      blue = maxColor;
      state = 4;
    }
  }

  if (state == 4)
  {
    red = 0;
    green = green - dall;
    if (green < 0) {
      green = 0;
      state=5;
    }
    blue = maxColor;
  }
  if (state == 5)
  {
    red = 0;
    green = 0;
    blue = blue -dall;
    if (blue <0)
    blue = 0;
    state = 1;    
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

  calcColors3();
  
  analogWrite(redLEDPin, red);
  analogWrite(greenLEDPin, green);
  analogWrite(blueLEDPin, blue);  
 
  u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );
  
  delay(10); 
}
