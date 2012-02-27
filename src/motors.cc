#include <iostream>
using namespace std;
#include "motors.h"

//Lmotor = motor1, Rmotor = motor2 
//Motor LMotor(1);

//#define LMotorPin 1
#define LMotorInvert 0 //NOT IMPLEMENTED
//#define RMotorPin 
#define RMotorInvert 0 //NOT IMPLEMENTED

Motor LMotor(LMotorPin);
Motor RMotor(RMotorPin);



Motor::Motor (int id) {
	switch (id)
	{
		case 1:
			motorid = MOTOR_1_GO; break;
		case 2:
			motorid = MOTOR_2_GO; break;
		case 3:
			motorid = MOTOR_3_GO; break;
		case 4:
			motorid = MOTOR_4_GO;
	}
	
}

void Motor::sendspeed()
{
	int speed;
	//cout << currentspeed << endl;
	if (currentspeed >127) {currentspeed = 127;} //in case speed is set too high
	//cout << currentspeed << endl;	
	speed = currentspeed;
	speed = speed bitor (dir << 7);
	//cout << speed << endl;
//	cout << dir;

//	Comms.init();
	Comms.sendcommand(motorid, speed);
}

void Motor::setspeed(int newspeed)
{
	currentspeed=newspeed;
	sendspeed();
}
