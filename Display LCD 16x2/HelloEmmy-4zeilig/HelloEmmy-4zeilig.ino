#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 20 chars and 4 line display
// 4 leitungen
// SCL an Analog5 (A5)
// SDA an Analog4 (A4)
// GND 
// VCC (5V)
LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup()
{
	// initialize the LCD
	lcd.begin();

	// Turn on the blacklight and print a message.
	lcd.backlight();
//  lcd.autoscroll();
}

int posX =0;
void loop()
{
lcd.clear();
lcd.setCursor(0,0); //Ab hier kann das I2C LCD Modul genau wie das einfache LCD Modul programmiert werden. 
lcd.print("Hallo Aaron");

lcd.setCursor(0,1);  // lcd.setCursor um Zeichen und Zeile anzugeben 
lcd.print("Du bist toll!"); // lcd.print um etwas auf dem Display anzeigen zu lassen. 

lcd.setCursor(0,2);  // lcd.setCursor um Zeichen und Zeile anzugeben 
lcd.print("Ein toller Junge!"); // lcd.print um etwas auf dem Display anzeigen zu lassen. 

lcd.setCursor(posX,3);  // lcd.setCursor um Zeichen und Zeile anzugeben 
lcd.print("Viel Erfolg!"); // lcd.print um etwas auf dem Display anzeigen zu lassen. 
posX++;
if (posX>7)
  posX=0;
delay(1000);

 }
