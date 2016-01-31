// UTFT_ViewFont (C)2014 Henning Karlsen
// web: http://www.henningkarlsen.com/electronics
//
// This program is a demo of the included fonts.
//
// This demo was made for modules with a screen resolution 
// of 320x240 pixels.
//
// This program requires the UTFT library.
//

#include <UTFT.h>

// Declare which fonts we will be using
extern uint8_t SmallFont[];
extern uint8_t BigFont[];
extern uint8_t UbuntuBold[];
extern uint8_t SevenSegNumFont[];
extern uint8_t DotMatrix_M_Slash[];

// Set the pins to the correct ones for your development shield
// ------------------------------------------------------------
// Arduino Uno / 2009:
// -------------------
// Standard Arduino Uno/2009 shield            : <display model>,A5,A4,A3,A2
// DisplayModule Arduino Uno TFT shield        : <display model>,A5,A4,A3,A2
//
// Arduino Mega:
// -------------------
// Standard Arduino Mega/Due shield            : <display model>,38,39,40,41
// CTE TFT LCD/SD Shield for Arduino Mega      : <display model>,38,39,40,41
//
// Remember to change the model parameter to suit your display module!
UTFT myGLCD(HX8357C,38,39,40,41);


int trigger=7;
int echo=6;
long dauer=0;
double entfernung=0;
double maxEntfernung = 0;

int piezo=5;

void calcDistance(void){
  digitalWrite(trigger, LOW);
  delay(5);
  digitalWrite(trigger, HIGH);
  delay(10);
  digitalWrite(trigger, LOW);
  dauer = pulseIn(echo, HIGH);
  entfernung = (dauer/2)/ 29.1;
  if (entfernung <0)
    entfernung = 0;
  if (entfernung >500)
    entfernung =500;
  
  // maximummerken
  if (entfernung > maxEntfernung)
    maxEntfernung = entfernung;
}


void setup()
{
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(piezo, OUTPUT);
  myGLCD.InitLCD();
  myGLCD.clrScr();
}


int calcBarLength(double val, int width, int maxi){
  if (val < 0) val = 0;
  if (val > maxi) val = maxi;
  
  int l = width*val/maxi;
  return l;
}


void loop()
{
  calcDistance();

// Hintergrund
  myGLCD.setBackColor(0, 0, 0);
// weißer Rahmen  
  myGLCD.setColor(255, 255, 255);  
  myGLCD.drawRect(5, 5, 475, 315);

// weiße Überschrift
  myGLCD.setFont(UbuntuBold);
  myGLCD.print("Distance:", CENTER, 40);


 

// Löschen der bisherige distanz
  myGLCD.setFont(UbuntuBold);
  myGLCD.setColor(0, 0, 0);  
  myGLCD.fillRect(10, 200, 460, 200+100);

// Distanz inch schreiben
  double inch = entfernung /2.54;
  myGLCD.setColor(0, 180, 255);  
  String out2 = " inch";
  myGLCD.print(inch + out2, 10, 200);


// Distanz cm schreiben
  myGLCD.setColor(0, 230, 255);  
  String out = " cm";
  myGLCD.print(entfernung + out, 10, 230);



// Bar
  int x = 20;
  int y = 265;
  int w = 440;
  int h = 10;
  myGLCD.setColor(0, 0, 0);  
  myGLCD.fillRect(x, y, x+w, y+h);
  myGLCD.setColor(0, 88, 255);  
  myGLCD.drawRect(x, y, x+w, y+h);

  int length = calcBarLength(entfernung, w, 500);
  myGLCD.setColor(0, 88, 255);  
  myGLCD.fillRect(x, y, x+length, y+h);

  
  // Piepen
  if(entfernung <= 10) {
    digitalWrite(piezo,HIGH);
    myGLCD.setFont(BigFont);
    myGLCD.setColor(255, 128, 0);  
    String outmax = "max: ";
    myGLCD.print("Alarm", CENTER, y+h+2);
  }  else  {
    digitalWrite(piezo,LOW);
  }
 
  delay(1000);
}

