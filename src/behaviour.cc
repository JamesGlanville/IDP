#include <iostream>
#include <cmath>
using namespace std;
#include "behaviour.h"


/* State variable:
 * 5 - following line until parallel line encountered. //5 arbitrary for now
*/

#define LIGHTSENSORJITTER 0.2


#define LMotorPin 1
#define LMotorInvert 0 //NOT IMPLEMENTED
#define RMotorPin 2
#define RMotorInvert 0 //NOT IMPLEMENTED

#define LFsensorPin 0
#define RFsensorPin 1


Behaviour::Behaviour() //init stuff
{
 /* 	LMotor = LMotor(LMotorPin);

	Motor RMotor(RMotorPin);
	adc LFsensor(LFsensorPin);
	adc RFsensor(RFsensorPin);

*/
//	LMotor.setdir(true);    RMotor.setdir(true);
}

void Behavior::poll()
{
	port1.readall();

}

void Behaviour::checkstate()
{
	//do something to jump to next state if needed.
}

void Behaviour::dostate()
{
	switch (state)
	{
		case 5:
			linefollow(); break;
	}
}

void Behaviour::linefollow()
{
//	if (abs(LFsensor.value -RFsensor.value) < LIGHTSENSORJITTER)
	if (port1.value & 0x0 !=
	{
		LMotor.setspeed(127);
		RMotor.setspeed(127);

	}
	if (LFsensor.value > RFsensor.value)
	{
		LMotor.setspeed(127);
		RMotor.setspeed(64);

	}
	else
	{
		LMotor.setspeed(64);
		RMotor.setspeed(127);
		
		
	}
}
