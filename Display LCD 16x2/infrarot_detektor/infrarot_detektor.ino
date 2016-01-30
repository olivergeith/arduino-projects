#include <LiquidCrystal.h>
#include <IRremote.h>

int cursorPos = 0;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int taster=7;
int RECV_PIN = 10;
int TMP36 = A0;
int temperatur = 0;
int temp[10];
int time= 20;
int tasterstatus=0;

IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
Serial.begin(9600);
lcd.begin(16, 2);
pinMode(taster, INPUT);
irrecv.enableIRIn();
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

tasterstatus=digitalRead(taster);
int fahrenheit = temperatur *1.8 +32;

if (irrecv.decode(&results)) {
  Serial.println(results.value, DEC);
  lcd.setCursor(0, 0);
  lcd.print("Code ");
  lcd.setCursor(5, 0);
  lcd.print(results.value);
  irrecv.resume();
}else{
  lcd.setCursor(0, 0);
  lcd.print("Code                    ");
}

 
Serial.print(temperatur);
Serial.println(" Grad Celsius");
// lcd.setCursor(0, 0);
// lcd.print("                ");

lcd.setCursor(0, 1);
if (tasterstatus == HIGH){
  lcd.print(fahrenheit);
  lcd.setCursor(3, 1);
  lcd.print(char(223));
  lcd.setCursor(4, 1);
  lcd.print("Fahrenheit");
}else{
  lcd.print(temperatur);
  lcd.setCursor(3, 1);
  lcd.print(char(223));
  lcd.setCursor(4, 1);
  lcd.print("Celsius   ");
}
delay(100);


}
