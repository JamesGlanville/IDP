#include <iostream>
using namespace std;
#include "motors.h"

Motor LMotor(LMotorPin,LMotorInvert);
Motor RMotor(RMotorPin,RMotorInvert);



Motor::Motor (int id,bool doinvert) {
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
	invert=doinvert;
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

void Motor::setdir(bool newdir)
{
	if (invert == false)
	{
		dir=newdir;
	}
	else
	{
		dir=!newdir;
	}
	sendspeed();

}
