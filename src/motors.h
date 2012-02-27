#ifndef MOTORS_H
#define MOTORS_H

#include <iostream>
using namespace std;
#include "comms.h"
//Lmotor = motor1, Rmotor = motor2 

#define LMotorPin 1
#define LMotorInvert false
#define RMotorPin 3
#define RMotorInvert true


class Motor {
	command_instruction motorid;
	bool invert;
	int ramptime; // 0 no ramping -> 255 slow ramping
	bool dir; //true = forward, false = backwards  WE MIGHT NEED TO REVERSE THIS FOR SIMPLICITY SO true means forwards left and rioght.
  public:
    Motor (int id,bool doinvert);
	float currentspeed;
    void setspeed(int newspeed);
    void sendspeed();
    void setdir(bool newdir);
    void setramp(int newramp){ramptime=newramp;Comms.sendcommand(RAMP_TIME, ramptime);}
};// LMotor(1),RMotor(2);
//extern Motor LMotor(1);
//Then, a trip point is setup as low value + ((high val
extern Motor LMotor;
extern Motor RMotor;


#endif
