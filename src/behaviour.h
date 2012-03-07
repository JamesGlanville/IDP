#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

#include <iostream>
#include <delay.h>

#include <fstream>
#include "comms.h"
#include "motors.h"
#include "adc.h"
#include "i2c.h"
#include "config.h"
#include "mechanism.h"

class Behaviour {
private:
	bool traversingjunction;
	int medals[5]; //1 - bronze, 2-silver, 3-gold, 0 - empty
	void querymedals();
	void flashTypeLEDs();
	friend class Movement;
	void areMedalsDone();
	void isMedalTypeDone();
  public:
	int standtype; //Which stand are we at? 0 if we're not.
	int state;
	fstream StateFile;
	void poll();
	void checkstate();
	void dostate();
	void junctionTojunction();
	void pressLED();
	void removeLED();
	void junctionTostand();
	void collectMedal();
	void standTojunction();
	void pressSideToPodiumSide();
	void rotateOnJunction(int dir);
	void depositMedal();
	Behaviour();

};

#endif
