#include <iostream>
using namespace std;
#include "motors.h"

//Lmotor = motor1, Rmotor = motor2 

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
	if (currentspeed >127) {currentspeed = 127;} //in case speed is set too high
	speed = currentspeed;
	speed = speed bitor (dir << 7);
//	Comms.init();
	Comms.sendcommand(motorid, speed);
}

void Motor::setspeed(int newspeed)
{
	currentspeed=newspeed;
	sendspeed();
}
