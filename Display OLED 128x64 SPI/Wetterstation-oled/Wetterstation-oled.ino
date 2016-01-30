#include "U8glib.h"

int TMP36 = A0;
int temperatur = 0;
int time= 20;

// Oled Display
int d0 = 8;
int d1 = 9;
int res = 10;
int dc = 11;
int cs = 12;
U8GLIB_SH1106_128X64 u8g(d0, d1, cs, dc, res);  

void drawtemp(void){
  int posTemp = 38;

  u8g.setFont(u8g_font_unifont);  // select font

  u8g.drawFrame(0,0,126,64);
  u8g.drawStr(5, 18, "Wetterstation");
  u8g.drawStr(5, posTemp, "Temp: ");  // put string of display at position X, Y

  u8g.setFont(u8g_font_helvB12);  // select font
  u8g.setPrintPos(50, posTemp);  // set position
  u8g.print(temperatur);  // display temperature from DHT11
  u8g.print(char(176));
  u8g.print('C');
}

int calcBarLength(int temp, int width, int maxi){
  int minTemp = 0;
  int maxTemp = maxi;
  if (temp < 0) temp = 0;
  if (temp > 50) temp = maxi;
  
  int l = width*temp/maxi;
  return l;
}

void drawBar(void){
  int top = 55;
  int x = 5;
  int h = 5;
  int w = 110;

  int maxTemp = 40;

  int length = calcBarLength(temperatur, w, maxTemp);
  u8g.drawFrame(x,top,w,h);
  u8g.drawBox  (x,top,length,h);

  // Linien
  for (int i=0; i<=maxTemp; i++){
    int p = calcBarLength(i, w, maxTemp);
    if (i%10 == 0){
      u8g.drawVLine(x+p,top-4,4);
      u8g.setFont(u8g_font_5x7);  // select font
      u8g.setPrintPos(x-2+p, top-5);  // set position
      u8g.print(i);  // i
    }else if (i%5 == 0){
      u8g.drawVLine(x+p,top-3,3);
    }//else{
     // u8g.drawVLine(x+p,top-2,2);
   // }
  }
}


void calcTemp(void){
 int temp[10];
 temp[0] = map(analogRead(TMP36), 0, 410, -50, 150);
  delay(time);
  temp[1] = map(analogRead(TMP36), 0, 410, -50, 150);
  delay(time);
  temp[2] = map(analogRead(TMP36), 0, 410, -50, 150);
  delay(time);
  temp[3] = map(analogRead(TMP36), 0, 410, -50, 150);
  delay(time);
  temp[4] = map(analogRead(TMP36), 0, 410, -50, 150);
  delay(time);
  temp[5] = map(analogRead(TMP36), 0, 410, -50, 150);
  delay(time);
  temp[6] = map(analogRead(TMP36), 0, 410, -50, 150);
  delay(time);
  temp[7] = map(analogRead(TMP36), 0, 410, -50, 150);
  delay(time);
  temp[8] = map(analogRead(TMP36), 0, 410, -50, 150);
  delay(time);
  temp[9] = map(analogRead(TMP36), 0, 410, -50, 150);
   
  temperatur=(temp[0]+temp[1]+temp[2]+temp[3]+temp[4]+temp[5]
  +temp[6]+temp[7]+temp[8]+temp[9])/10; // Alles in eine Zeile!
}

void setup(void) {
}

void loop(void) {
  calcTemp();
  u8g.firstPage();  
  do {
    drawtemp();
    drawBar();
  } while( u8g.nextPage() );
  
  delay(100);  // Delay of 5sec before accessing DHT11 (min - 2sec)
}
