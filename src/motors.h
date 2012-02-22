#include <iostream>
using namespace std;
#include "comms.h"
//Lmotor = motor1, Rmotor = motor2 

class Motor {
	command_instruction motorid;
	int ramptime; // 0 no ramping -> 255 slow ramping
	float currentspeed;
	bool dir; //true = forward, false = backwards
  public:
    Motor (int);
    void setspeed(int newspeed);
    void sendspeed();
    void setdir(bool newdir){dir=newdir;sendspeed();}
    void setramp(int newramp){ramptime=newramp;Comms.sendcommand(RAMP_TIME, ramptime);}
};// LMotor(1),RMotor(2);
//extern Motor LMotor(1);
