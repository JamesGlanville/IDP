#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H


#include <iostream>

#include "comms.h"
#include "motors.h"
#include "adc.h"
#include "i2c.h"

#define LMotorPin 1
#define LMotorInvert 0 //NOT IMPLEMENTED
#define RMotorPin 2
#define RMotorInvert 0 //NOT IMPLEMENTED

class Behaviour {
private:
 //	Motor LMotor(int a);

  public:

	int state;
	void poll();
	void checkstate();
	void dostate();
	void linefollow();
	Behaviour();

};// LMotor(1),RMotor(2);
//extern Motor LMotor(1);

#endif
