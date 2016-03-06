/*************************************************
 ** 						**
 **  Based on Arduino Library Stepper.h		**
 **  http://www.arduino.cc/en/Tutorial/Stepper	**
 ** 						**
 **  Downloaded from:				**
 **  www.arduino-projekte.de			**
 **						**
 *************************************************/

#ifndef AH_28BYJ48_h
#define AH_28BYJ48_h

class AH_28BYJ48 {
public:
	// constructors:
	AH_28BYJ48(int number_of_steps, int motor_pin_1, int motor_pin_2, int motor_pin_3, int motor_pin_4);

	// speed setter method:
	void setSpeedRPM(long Speed);
	void setSpeedHz(long Speed);

	// mover method:
	void step(int number_of_steps);

private:
	void stepMotorOnePhase(int this_step);
	void stepMotorTwoPhase(int this_step);
	void stepMotor(int this_step);

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

#endif

/*
 Based on Arduino Library Stepper.h
 */

#ifndef AH_28BYJ48_h
#define AH_28BYJ48_h

class AH_28BYJ48 {
public:
	// constructors:
	Stepper(int number_of_steps, int motor_pin_1, int motor_pin_2, int motor_pin_3, int motor_pin_4);

	// speed setter method:
	void setSpeed(long whatSpeed);

	// mover method:
	void stepForward(int number_of_steps);
	void stepBackward(int number_of_steps);

	int version(void);

private:
	void stepMotor(int this_step);

	int direction;// Direction of rotation
	int speed;// Speed in RPMs
	unsigned long step_delay;// delay between steps, in ms, based on speed
	int number_of_steps;// total number of steps this motor can take
	int pin_count;// whether you're driving the motor with 2 or 4 pins
	int step_number;// which step the motor is on

	// motor pin numbers:
	int motor_pin_1;
	int motor_pin_2;
	int motor_pin_3;
	int motor_pin_4;

	long last_step_time;// time stamp in ms of when the last step was taken
};

#endif

