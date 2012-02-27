#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

#include <iostream>

#include "comms.h"
#include "motors.h"
#include "adc.h"
#include "i2c.h"

class Behaviour {
private:

  public:

	int state;
	void poll();
	void checkstate();
	void dostate();
	void linefollow();
	Behaviour();

};

#endif
