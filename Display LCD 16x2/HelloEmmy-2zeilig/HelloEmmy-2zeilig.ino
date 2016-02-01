#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
// 4 leitungen
// SCL an Analog5 (A5)
// SDA an Analog4 (A4)
// GND 
// VCC (5V)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
	// initialize the LCD
	lcd.begin();

	// Turn on the blacklight and print a message.
	lcd.backlight();
//  lcd.autoscroll();
}

void loop()
{
lcd.setCursor(0,0); //Ab hier kann das I2C LCD Modul genau wie das einfache LCD Modul programmiert werden. 

lcd.print("Hallo Emmy");

lcd.setCursor(0,1);  // lcd.setCursor um Zeichen und Zeile anzugeben 

lcd.print("Viel Erfolg!"); // lcd.print um etwas auf dem Display anzeigen zu lassen. 

 }
