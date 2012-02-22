#include <iostream>
using namespace std;
#include "comms.h"
//Lmotor = motor1, Rmotor = motor2 

class adc {
//	int value;
	request_instruction adc_id;
  public:
    adc (int id);
	int getvalue();
};// LMotor(1),RMotor(2);
//extern Motor LMotor(1);
