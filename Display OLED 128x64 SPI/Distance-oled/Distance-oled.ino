#include "U8glib.h"

// Oled Display
int d0 = 8;
int d1 = 9;
int res = 10;
int dc = 11;
int cs = 12;
U8GLIB_SH1106_128X64 u8g(d0, d1, cs, dc, res);  


// other pins
int trigger=7;
int echo=6;
long dauer=0;
long entfernung=0;



void draw(void){
  int posX = 38;

  u8g.setFont(u8g_font_unifont);  // select font

  u8g.drawFrame(0,0,126,64);
  u8g.drawStr(5, 18, "Entfernung");
  u8g.drawStr(5, posX, "cm: ");  // put string of display at position X, Y

  u8g.setFont(u8g_font_helvB12);  // select font
  u8g.setPrintPos(50, posX);  // set position
  u8g.print(entfernung);  // 
 }

int calcBarLength(long val, int width, int maxi){
  if (val < 0) val = 0;
  if (val > maxi) val = maxi;
  
  int l = width*val/maxi;
  return l;
}

void drawBar(void){
  int top = 55;
  int x = 5;
  int h = 5;
  int w = 110;

  int maxi = 500;

  int length = calcBarLength(entfernung, w, maxi);
  u8g.drawFrame(x,top,w,h);
  u8g.drawBox  (x,top,length,h);

  // Linien
  for (int i=0; i<=maxi; i=i+25){
    int p = calcBarLength(i, w, maxi);
    if (i%100 == 0){
      u8g.drawVLine(x+p,top-4,4);
      u8g.setFont(u8g_font_5x7);  // select font
      u8g.setPrintPos(x-2+p, top-5);  // set position
      u8g.print(i);  // i
    }else if (i%25 == 0){
      u8g.drawVLine(x+p,top-1,1);
    }//else{
     // u8g.drawVLine(x+p,top-2,2);
   // }
  }
}

void calcDistance(void){
  digitalWrite(trigger, LOW);
  delay(5);
  digitalWrite(trigger, HIGH);
  delay(10);
  digitalWrite(trigger, LOW);
  dauer = pulseIn(echo, HIGH);
  entfernung = (dauer/2) / 29.1;
}


void setup(void) {
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
}

void loop(void) {
  calcDistance();
  u8g.firstPage();  
  do {
    draw();
    drawBar();
  } while( u8g.nextPage() );
  
  delay(1000);  // Delay of 5sec before accessing DHT11 (min - 2sec)
}
