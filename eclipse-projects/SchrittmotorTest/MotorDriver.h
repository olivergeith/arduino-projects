/*
 * MotorDriver.h
 *
 *  Created on: 02.03.2016
 *      Author: Oliver
 */

#ifndef MOTORDRIVER_H_
#define MOTORDRIVER_H_

class MotorDriver {
public:
	// constructors:
	MotorDriver(int number_of_steps, int motor_pin_1, int motor_pin_2, int motor_pin_3, int motor_pin_4, int phases);
	virtual ~MotorDriver();

	// speed setter method:
	void setSpeedRPM(long Speed);
	void setSpeedHz(long Speed);

	// mover method:
	void step(int number_of_steps);

private:
	void stepMotorOnePhase(int this_step);
	void stepMotorTwoPhase(int this_step);
	void stepMotor(int this_step);

	int phases;        	// How many Phases
	int direction;        	// Direction of rotation
	int speed;            	// Speed in RPMs
	unsigned long step_delay;   // delay between steps, in ms, based on speed
	int number_of_steps;      	// total number of steps this motor can take
	int step_number;        	// which step the motor is on

	// motor pin numbers:
	int motor_pin_1;  		//blue
	int motor_pin_2;  		//pink
	int motor_pin_3;  		//yellow
	int motor_pin_4;  		//orange

	long last_step_time;      	// time stamp in ms of when the last step was taken

};

#endif /* MOTORDRIVER_H_ */
