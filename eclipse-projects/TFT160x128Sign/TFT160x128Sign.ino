// UTFT_Demo_160x128_Serial (C)2013 QDtech Co.,LTD
// This program is a demo of how to use most of the functions
// of the library with a supported display modules.
//
// This demo was made for modules with a screen resolution
// of 160x128 pixels.
//
// This program requires the UTFT library.
//

#include <UTFT160.h>

//for QD_TFT180X SPI LCD Modle
//http://www.QDtech.net
//http://qdtech.taobao.com
//How to Use the Module Hardware in ArduinoUNO:
//1.BL should be Connect to any IO to Control ,or you can Connect it to VCC so that the BackLight will be alway on.
//2.VCC is Connect to 5V DC.
//3.Every IO should be Connect a Resistor  value between 500ohm~2Kohm in series.
//Param1:Value Can be:QD_TFT180A/QD_TFT180B/QD_TFT180C
//QD_TFT180A is for ST7735,QD_TFT180B_is for HX8353,QD_TFT180C is for S6D02A1
//Param2 instructions:Connect to LCD_Pin SDA/SDI/MOSI(it means LCD_Model Pin_SDA/SDI/MOSI Connect to Arduino_UNO Pin11)
//Param3 instructions:Connect to LCD_Pin SCL/CLK/SCLK(it means LCD_Model Pin_SCL/CLK/SCLK Connect to Arduino_UNO Pin10)
//Param4 instructions:Connect to LCD_Pin CS/CE(it means LCD_Model Pin_CS/CE Connect to Arduino_UNO Pin9)
//Param5 instructions:Connect to LCD_Pin RST/RESET(it means LCD_Model Pin_RST/RESET Connect to Arduino_UNO Pin12)
//Param6 instructions:Connect to LCD_Pin RS/DC(it means LCD_Model Pin_RS/DC Connect to Arduino_UNO Pin8)
UTFT myGLCD(QD_TFT180B, //
		9, // LCD_Pin SDA/SDI/MOSI(it means LCD_Model Pin_SDA/SDI/MOSI Connect to Arduino_UNO Pin11)
		8, // LCD_Pin SCL/CLK/SCLK(it means LCD_Model Pin_SCL/CLK/SCLK Connect to Arduino_UNO Pin10)
		11,  // LCD_Pin CS/CE(it means LCD_Model Pin_CS/CE Connect to Arduino_UNO Pin9)
		12, // LCD_Pin RST/RESET(it means LCD_Model Pin_RST/RESET Connect to Arduino_UNO Pin12)
		10); // LCD_Pin RS/DC(it means LCD_Model Pin_RS/DC Connect to Arduino_UNO Pin8)
// Remember to change the model parameter to suit your display module!

// Declare which fonts we will be using
//extern uint8_t BigFont[];
extern uint8_t SmallFont[];
extern uint8_t CalibriBold32x48[];
extern uint8_t Arial_round_16x24[];

void setup() {
	randomSeed(analogRead(0));

// Setup the LCD
	myGLCD.InitLCD();
	myGLCD.clrScr();
}

void drawEmptySign(int r, int g, int b) {
	myGLCD.clrScr();
	myGLCD.setColor(r, g, b);
	myGLCD.setBackColor(r, g, b);
	myGLCD.fillRoundRect(0, 10, 159, 117);
	myGLCD.setColor(255, 255, 255);
	myGLCD.drawRoundRect(2, 12, 157, 115);
	myGLCD.drawRoundRect(3, 13, 156, 114);
	myGLCD.drawRoundRect(4, 14, 155, 113);
}

void drawSpeedLimitSign(String speed) {
	myGLCD.clrScr();
	myGLCD.setColor(255, 255, 255);
	myGLCD.setBackColor(255, 255, 255);
	myGLCD.fillRoundRect(20, 0, 139, 127);
	myGLCD.setColor(0, 0, 0);
	myGLCD.drawRoundRect(22, 2, 137, 125);
	myGLCD.drawRoundRect(23, 3, 136, 124);
	myGLCD.drawRoundRect(24, 4, 135, 123);

	myGLCD.setFont(Arial_round_16x24);
	myGLCD.setColor(0, 0, 0);
	myGLCD.print("SPEED", CENTER, 15);
	myGLCD.print("LIMIT", CENTER, 40);

	myGLCD.setFont(CalibriBold32x48);
	myGLCD.print(speed, CENTER, 65);

}

void drawEmptyGreenSign() {
	drawEmptySign(0, 160, 32);
}

void drawEmptyBlueSign() {
	drawEmptySign(0, 0, 128);
}

void drawAutoBahn() {
	myGLCD.setFont(Arial_round_16x24);
	myGLCD.setColor(255, 255, 255);
	myGLCD.print("AUTOBAHN", CENTER, 34);

	myGLCD.setFont(SmallFont);
	myGLCD.print("No Speed Limit", CENTER, 80);
}

void drawNextService() {
	myGLCD.setFont(Arial_round_16x24);
	myGLCD.setColor(255, 255, 255);
	myGLCD.print("Next", CENTER, 20);
	myGLCD.print("Service", CENTER, 44);

	myGLCD.setFont(SmallFont);
	myGLCD.print("in 66 Miles", CENTER, 80);
}

void drawDonutHeaven() {
	myGLCD.setFont(Arial_round_16x24);
	myGLCD.setColor(255, 255, 255);
	myGLCD.print("DONUTS", CENTER, 20);
	myGLCD.print("& COFFEE", CENTER, 44);

	myGLCD.setFont(SmallFont);
	myGLCD.print("Next Exit", CENTER, 78);
	myGLCD.print("Turn Right", CENTER, 92);
}

void drawFreeway() {
	myGLCD.setFont(Arial_round_16x24);
	myGLCD.setColor(255, 255, 255);
	myGLCD.print("FREEWAY", CENTER, 34);

	myGLCD.setFont(SmallFont);
	myGLCD.print("Don't drink", CENTER, 78);
	myGLCD.print("and drive!", CENTER, 92);
}

void loop() {
	int buf[158];
	int x, x2;
	int y, y2;
	int r;

	drawSpeedLimitSign("65");
	delay(5000);

	drawEmptySign(255, 128, 0);
	drawDonutHeaven();
	delay(5000);

	drawEmptyBlueSign();
	drawNextService();
	delay(5000);

	drawEmptyBlueSign();
	drawAutoBahn();
	delay(5000);

	drawEmptyGreenSign();
	drawFreeway();
	delay(5000);
}
