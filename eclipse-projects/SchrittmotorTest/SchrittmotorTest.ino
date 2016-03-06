/********************************************************
 **  Downloaded from:                                   **
 **  http://www.arduino-projekte.de                     **
 ********************************************************/

#include "MotorDriver.h"

const int stepsPerRevolution = 64 * 64;  // number of steps per revolution * gear factor

// initialize the library
MotorDriver myStepper(stepsPerRevolution, 8, 9, 10, 11, 1);

void setup() {
	Serial.begin(9600);
}

void loop() {
//	myStepper.setSpeedRPM(5);
	myStepper.setSpeedHz(5);
	myStepper.step(stepsPerRevolution / 2);
	delay(2000);
	myStepper.step(-stepsPerRevolution / 2);
	delay(2000);
	myStepper.step(400);
	delay(1000);
	myStepper.step(-800);
	delay(1000);
	myStepper.step(400);
	delay(1000);
}

