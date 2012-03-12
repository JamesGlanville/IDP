#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
using namespace std;

#define LMotorPin 1
#define LMotorInvert true
#define LMotorScale 1
#define RMotorPin 2
#define RMotorInvert false
#define RMotorScale 0.92

const unsigned int RAMPT = 50;
const unsigned int RAMPLESS = 5; //Amount to un-ramp every loop when line following.

//port 1:
#define PORT1ADDR 7
const unsigned int RFsensor = 1;
const unsigned int LFsensor = 2;
const unsigned int RMsensor = 4;
const unsigned int LMsensor = 8;
const unsigned int actuatorA = 16;
const unsigned int actuatorB = 32;
const unsigned int bumperA = 64;
const unsigned int bumperB = 128;

//port2
#define PORT2ADDR 6
const unsigned int RELOAD = 1;
const unsigned int REMOVE = 2;
const unsigned int TURNMOT = 4;
const unsigned int TURNSWITCH = 8;
const unsigned int BMEDAL = 16;
const unsigned int SMEDAL = 32;
const unsigned int GMEDAL = 64;
const unsigned int PRESSSWITCH = 128;

//ADC:
const unsigned int distancepin = 0;
const unsigned int ldrpin = 1;
const unsigned int thicknesspin = 2;

//ADC Decision Values

const unsigned int LowerBoundLDR = 100;
const unsigned int UpperBoundLDR = 200;

//DELAYS

const int RaiseClawDelay = 500;
const int LowerClawDelay = 500;
const int AdvanceGripperDelay = 500;
const int RetractGripperDelay = 500;

const int InitialAdvanceDelay = 20; //Initial turntable advance delay to get off the switch

#define FASTSPEED 127
#define SLOWSPEED 64

#define MEDALLEDTIME 800 //ms to turn medal indicator leds on for.

#define LEFT 0 //Really anticlockwise when viewed from top.
#define RIGHT 1

#define TURNWAIT 1000

//int standtypeorder[]={1,2,3}; //1 - bronze, 2 - silver, 3 - gold

#endif
