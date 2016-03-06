/*
 * MotorDriver.cpp
 *
 *  Created on: 02.03.2016
 *      Author: Oliver
 */

#include "Arduino.h"
#include "MotorDriver.h"

MotorDriver::MotorDriver(int number_of_steps, int motor_pin_1, int motor_pin_2, int motor_pin_3, int motor_pin_4, int phases) {
	this->step_number = 0;      			// which step the motor is on
	this->speed = 0;      			// the motor speed, in revolutions per minute
	this->direction = 0;      			// motor direction
	this->last_step_time = 0;      			// time stamp in ms of the last step taken
	this->number_of_steps = number_of_steps;      			// total number of steps for this motor
	this->phases = phases;

	// Arduino pins for the motor control connection:
	this->motor_pin_1 = motor_pin_1;
	this->motor_pin_2 = motor_pin_2;
	this->motor_pin_3 = motor_pin_3;
	this->motor_pin_4 = motor_pin_4;

	// setup the pins on the microcontroller:
	pinMode(this->motor_pin_1, OUTPUT);
	pinMode(this->motor_pin_2, OUTPUT);
	pinMode(this->motor_pin_3, OUTPUT);
	pinMode(this->motor_pin_4, OUTPUT);

}

MotorDriver::~MotorDriver() {
	// TODO Auto-generated destructor stub
}

//******************************************************************************************

void MotorDriver::setSpeedRPM(long Speed) {
	this->step_delay = 60L * 1000L / this->number_of_steps / Speed;
}

//******************************************************************************************

void MotorDriver::setSpeedHz(long Speed) {
	this->step_delay = 1000 / Speed;
}

//******************************************************************************************

void MotorDriver::step(int steps_to_move) {
	int steps_left = abs(steps_to_move);  // how many steps to take

	if (steps_to_move > 0) {
		this->direction = 1;
	}
	if (steps_to_move < 0) {
		this->direction = 0;
	}

	while (steps_left > 0) {

		if (millis() - this->last_step_time >= this->step_delay) {

			this->last_step_time = millis();

			if (this->direction == 1) {
				this->step_number++;
				if (this->step_number == this->number_of_steps) {
					this->step_number = 0;
				}
			} else {
				if (this->step_number == 0) {
					this->step_number = this->number_of_steps;
				}
				this->step_number--;
			}

			steps_left--;
			switch (phases) {
			default:
			case 1:
				stepMotorOnePhase(this->step_number);
				break;
			case 2:
				stepMotorTwoPhase(this->step_number);
				break;
			case 3:
				stepMotor(this->step_number);
				break;
			}
		}
	}
}

//******************************************************************************************
// double Precision
void MotorDriver::stepMotor(int thisStep) {
	switch (thisStep % 8) {
	case 0:
		digitalWrite(motor_pin_1, LOW);  //BLU
		digitalWrite(motor_pin_2, LOW);  //Pink
		digitalWrite(motor_pin_3, LOW);  //Yellow
		digitalWrite(motor_pin_4, HIGH); //Orange
		break;
	case 1:
		digitalWrite(motor_pin_1, LOW);  //BLU
		digitalWrite(motor_pin_2, LOW);  //Pink
		digitalWrite(motor_pin_3, HIGH); //Yellow
		digitalWrite(motor_pin_4, HIGH); //Orange
		break;
	case 2:
		digitalWrite(motor_pin_1, LOW);  //BLU
		digitalWrite(motor_pin_2, LOW);  //Pink
		digitalWrite(motor_pin_3, HIGH); //Yellow
		digitalWrite(motor_pin_4, LOW);  //Orange
		break;
	case 3:
		digitalWrite(motor_pin_1, LOW);  //BLU
		digitalWrite(motor_pin_2, HIGH); //Pink
		digitalWrite(motor_pin_3, HIGH); //Yellow
		digitalWrite(motor_pin_4, LOW);  //Orange
		break;
	case 4:
		digitalWrite(motor_pin_1, LOW);  //BLU
		digitalWrite(motor_pin_2, HIGH); //Pink
		digitalWrite(motor_pin_3, LOW);  //Yellow
		digitalWrite(motor_pin_4, LOW);  //Orange
		break;
	case 5:
		digitalWrite(motor_pin_1, HIGH);  //BLU
		digitalWrite(motor_pin_2, HIGH);  //Pink
		digitalWrite(motor_pin_3, LOW);   //Yellow
		digitalWrite(motor_pin_4, LOW);   //Orange
		break;
	case 6:
		digitalWrite(motor_pin_1, HIGH);  //BLU
		digitalWrite(motor_pin_2, LOW);  //Pink
		digitalWrite(motor_pin_3, LOW);  //Yellow
		digitalWrite(motor_pin_4, LOW);  //Orange
		break;
	case 7:
		digitalWrite(motor_pin_1, HIGH); //BLU
		digitalWrite(motor_pin_2, LOW);  //Pink
		digitalWrite(motor_pin_3, LOW);  //Yellow
		digitalWrite(motor_pin_4, HIGH); //Orange
		break;
	}

}

//******************************************************************************************

void MotorDriver::stepMotorOnePhase(int thisStep) {
	switch (thisStep % 4) {
	case 0:
		digitalWrite(motor_pin_1, HIGH);  //BLU
		digitalWrite(motor_pin_2, LOW);  //Pink
		digitalWrite(motor_pin_3, LOW);  //Yellow
		digitalWrite(motor_pin_4, LOW); //Orange
		break;
	case 1:
		digitalWrite(motor_pin_1, LOW);  //BLU
		digitalWrite(motor_pin_2, HIGH);  //Pink
		digitalWrite(motor_pin_3, LOW); //Yellow
		digitalWrite(motor_pin_4, LOW); //Orange
		break;
	case 2:
		digitalWrite(motor_pin_1, LOW);  //BLU
		digitalWrite(motor_pin_2, LOW);  //Pink
		digitalWrite(motor_pin_3, HIGH); //Yellow
		digitalWrite(motor_pin_4, LOW);  //Orange
		break;
	case 3:
		digitalWrite(motor_pin_1, LOW);  //BLU
		digitalWrite(motor_pin_2, LOW); //Pink
		digitalWrite(motor_pin_3, LOW); //Yellow
		digitalWrite(motor_pin_4, HIGH);  //Orange
		break;
	}
}

void MotorDriver::stepMotorTwoPhase(int thisStep) {
	switch (thisStep % 4) {
	case 0:
		digitalWrite(motor_pin_1, HIGH);  //BLU
		digitalWrite(motor_pin_2, HIGH);  //Pink
		digitalWrite(motor_pin_3, LOW);  //Yellow
		digitalWrite(motor_pin_4, LOW); //Orange
		break;
	case 1:
		digitalWrite(motor_pin_1, LOW);  //BLU
		digitalWrite(motor_pin_2, HIGH);  //Pink
		digitalWrite(motor_pin_3, HIGH); //Yellow
		digitalWrite(motor_pin_4, LOW); //Orange
		break;
	case 2:
		digitalWrite(motor_pin_1, LOW);  //BLU
		digitalWrite(motor_pin_2, LOW);  //Pink
		digitalWrite(motor_pin_3, HIGH); //Yellow
		digitalWrite(motor_pin_4, HIGH);  //Orange
		break;
	case 3:
		digitalWrite(motor_pin_1, HIGH);  //BLU
		digitalWrite(motor_pin_2, LOW); //Pink
		digitalWrite(motor_pin_3, LOW); //Yellow
		digitalWrite(motor_pin_4, HIGH);  //Orange
		break;
	}

}
