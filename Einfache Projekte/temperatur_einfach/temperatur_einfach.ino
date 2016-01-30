#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int TMP36 = A0;
int temperatur = 0;
int temp[10];
int time= 20;

void setup() {
Serial.begin(9600);
lcd.begin(16, 2);
}


void loop() {
 
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
 
Serial.print(temperatur);
Serial.println(" Grad Celsius");

lcd.setCursor(0, 0);
lcd.print("Temperatur");
lcd.setCursor(0, 1);
lcd.print(temperatur + " °C");


}
