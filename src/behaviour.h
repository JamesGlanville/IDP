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

class Behaviour {
private:
	bool traversingjunction;
  public:

	int state;
	fstream StateFile;
	void poll();
	void checkstate();
	void dostate();
	void junctionTojunction();
	void pressLED();
	void junctionTostand();
	void collectMedal();
	void standTojunction();
	Behaviour();

};

#endif
