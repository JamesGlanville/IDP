#include <iostream>
#include <cmath>
using namespace std;
#include "behaviour.h"


/* State variable:
 * 5 - following line until parallel line encountered. //5 arbitrary for now
*/

Behaviour::Behaviour() //init stuff
{
	i2c port1(PORT1ADDR);
	//port1.value= LFsensor & RFsensor; //set pins for input
	port1.value=255;
	port1.writeall();


//	LMotor.setdir(true);    RMotor.setdir(true);
}

void Behaviour::poll()
{
	port1.readall();
//	cout << port1.value;

}

void Behaviour::checkstate()
{
	//do something to jump to next state if needed.
}

void Behaviour::dostate()
{
	switch (state)
	{
		case 1: //Getting to press, junctionTojunction x3
			junctionTojunction(); break;
		case 2:
			junctionTojunction(); break;
		case 3:
			junctionTojunction(); break;
		case 4: //PressLED
			pressLED(); break;
		case 5:
			junctionTostand(); break;
		case 6:
			collectMedal(); break;
		case 7:
			standTojunction(); break;
	}
}

void Behaviour::pressLED()
{
	cout << "LEDLEDLEDLEDLED!" << endl;
	port2.value = port2.value | RELOAD;
	port2.writeall();
	delay(100);
	port2.value = port2.value ^ RELOAD;
	port2.writeall();
	state++;
}

void Behaviour::junctionTojunction()
{
	LMotor.setdir(true);
	RMotor.setdir(true);
	if (traversingjunction) {cout << "traversing" << endl;}
//	cout << (port1.value & LFsensor) << (port1.value & RFsensor) << endl;
	

	if (((port1.value & LFsensor) == 0) && ((port1.value & RFsensor) == 0))
	{
		if (traversingjunction == true)
		{
			state++;
		}		

		cout << "Straight ahead" << endl;
		LMotor.setspeed(127);
		RMotor.setspeed(127);

	}
	if (((port1.value & LFsensor) == 0) && ((port1.value & RFsensor) != 0))

	{
		cout << "Turn right" << endl;
		if (!traversingjunction)
		{
			LMotor.setspeed(FASTSPEED);
			RMotor.setspeed(SLOWSPEED);
		}
		else
		{
			LMotor.setspeed(SLOWSPEED);
			RMotor.setspeed(FASTSPEED);
		}
	}
	if (((port1.value & LFsensor) != 0) && ((port1.value & RFsensor) == 0))
	{
		cout << "Turn left" << endl;
		if (!traversingjunction)
		{
			LMotor.setspeed(SLOWSPEED);
			RMotor.setspeed(FASTSPEED);
		}
		else
		{
			LMotor.setspeed(FASTSPEED);
			RMotor.setspeed(SLOWSPEED);
		}
	}
	
	if (((port1.value & LFsensor) != 0) && ((port1.value & RFsensor) != 0))
	{
		cout << "Hit perp line" << endl;
		//need to advance until one sensor gets over line, then use opposite of normal algo.
		LMotor.setspeed(127);
		RMotor.setspeed(127);
		traversingjunction = true;		
	}

}
