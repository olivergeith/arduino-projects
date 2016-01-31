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

  u8g.setFont(u8g_font_unifont);  // select font
  u8g.drawFrame(0,0,126,64);
  u8g.drawStr(5, 16, "Lauflicht");
  int posX = 0;
  for (int i = 2; i<8;i++){
    u8g.setPrintPos(5, 50);  // set position
    u8g.print(current);  // 

    posX = 5 + (i-2) *10; 
    if (current == i){
      setPin(i, true);
      u8g.drawStr(posX, 32, "o");
    }else{
      setPin(i, false);
      u8g.drawStr(posX, 32, "");
    }
  }
 }




void setup(void) {
  pinMode(p1, OUTPUT);
  pinMode(p2, OUTPUT);
  pinMode(p3, OUTPUT);
  pinMode(p4, OUTPUT);
  pinMode(p5, OUTPUT);
  pinMode(p6, OUTPUT);
}

int inkrement = 1;

void loop(void) {
  u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );

  current = current + inkrement;
  if (current==7)
  {
    inkrement = -1;
  }else if (current == 2){
    inkrement = 1;
  }
  delay(10); 
}
