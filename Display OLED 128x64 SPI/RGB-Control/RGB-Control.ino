#include "U8glib.h"

// Oled Display
int d0 = 8;
int d1 = 9;
int res = 10;
int dc = 11;
int cs = 12;
U8GLIB_SH1106_128X64 u8g(d0, d1, cs, dc, res);  


// Ledpins
int p1 = 2; 
int p2 = 3; 
int p3 = 4; 
int p4 = 5; 
int p5 = 6; 
int p6 = 7; 
//int p7 = 8; 

int current = 2;

void setPin(int pin, boolean on)
{
  if (on == true)
    digitalWrite(pin, HIGH);
  else
    digitalWrite(pin, LOW);
}


void draw(void){
  înt posX = 5+ current*10; 

  u8g.setFont(u8g_font_unifont);  // select font
  u8g.drawFrame(0,0,126,64);
  u8g.drawStr(posX, 16, "Lauflicht");

  for (int i = 2; i<8;i++){
    if (current == i){
      setPin(i, true)
      u8g.drawStr(posX, 32, "O");
    }else{
      setPin(i, false)
    }
  }
  current++;
  if (current>7)
    current = 2;
 }




void setup(void) {
  pinMode(p1, OUTPUT);
  pinMode(p2, OUTPUT);
  pinMode(p3, OUTPUT);
  pinMode(p4, OUTPUT);
  pinMode(p5, OUTPUT);
  pinMode(p6, OUTPUT);
}

void loop(void) {
  u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );
  delay(200); 
}
