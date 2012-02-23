#ifndef ADC_H
#define ADC_H



#include <iostream>
using namespace std;
#include "comms.h"
//Lmotor = motor1, Rmotor = motor2 

#define LFsensorPin 0
#define RFsensorPin 1

class adc {
//	int value;
	request_instruction adc_id;
  public:
	int value;
    adc (int id);
	int getvalue();
};// LMotor(1),RMotor(2);
//extern Motor LMotor(1);
	extern adc LFsensor(LFsensorPin);
	extern adc RFsensor(RFsensorPin);

#endif
