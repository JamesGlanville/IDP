#include <iostream>
using namespace std;
#include "motors.h"

Motor LMotor(LMotorPin,LMotorInvert,LMotorScale);
Motor RMotor(RMotorPin,RMotorInvert,RMotorScale);



Motor::Motor (int id,bool doinvert,float setscale) {
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
	scale=setscale;
}

void Motor::sendspeed()
{
	int speed;
	if (currentspeed >127) {currentspeed = 127;} //in case speed is set too high
	speed = currentspeed*scale;
	speed = speed bitor (dir << 7);
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
