/*
 * Mode.h
 *
 *  Created on: 11.02.2016
 *      Author: Oliver
 */

#ifndef MODE_H_
#define MODE_H_

class Mode {
public:
	Mode();
	virtual ~Mode();

	char* getCurrentMode();
	void increment();
//	void decrement();
	int getCurrentModeInt();
private:
	int mode;
	int MAXMODE = 5;

};

#endif /* MODE_H_ */
