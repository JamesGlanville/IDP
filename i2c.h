#include <iostream>
using namespace std;
#include "comms.h"

//Lmotor = motor1, Rmotor = motor2 

class i2c {
	request_instruction readname;
	command_instruction writename;
	int port;


public:
	i2c(int id);
	int value;
	void readall();
		void writeall();

};// LMotor(1),RMotor(2);
//extern Motor LMotor(1);

