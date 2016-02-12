/*
 * Mode.h
 *
 *  Created on: 11.02.2016
 *      Author: Oliver
 */

#ifndef MENU_H_
#define MENU_H_

class Menu {
public:
	Menu(int maxMode);
	virtual ~Menu();

	char* getCurrentMode();
	void increment();
//	void decrement();
	int getCurrentModeInt();
private:
	int mode;
	int MAXMODE;
};

#endif /* MENU_H_ */
