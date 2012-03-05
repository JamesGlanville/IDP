#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
using namespace std;

#define LMotorPin 1
#define LMotorInvert false
#define LMotorScale 1
#define RMotorPin 2
#define RMotorInvert true
#define RMotorScale 0.92

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
const unsigned int pressswitch = 128;

//ADC:
const unsigned int distancepin = 0;
const unsigned int ldrpin = 1;
const unsigned int thicknesspin = 2;


#define FASTSPEED 127
#define SLOWSPEED 64

#endif
