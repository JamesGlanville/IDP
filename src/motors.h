#ifndef MOTORS_H
#define MOTORS_H

#include <iostream>
#include "comms.h"
#include "config.h"
using namespace std;


class Motor {
	float scale; //Hack to try and get "full speed" speed the same for all motors.
	command_instruction motorid;
	bool invert; //We want to make "forwards" rotation move the robot forwards.
	int ramptime; // 0 no ramping -> 255 slow ramping
	bool dir; //true = forward, false = backwards
  public:
    Motor (int id,bool doinvert,float setscale);
	float currentspeed;
    void setspeed(int newspeed);
    void sendspeed();
    void setdir(bool newdir);
    void setramp(int newramp){ramptime=newramp;Comms.sendcommand(RAMP_TIME, ramptime);}
};

extern Motor LMotor;
extern Motor RMotor;


#endif
