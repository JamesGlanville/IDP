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
		case 5:
		//	cout << 1;
			//cout << port1.value | LFsensor;
			//port1.value 
		//	port1.value |= LFsensor;
			//port1.value = port1.value | RFsensor;
			linefollow(); break;
	}
}

void Behaviour::linefollow()
{
//	cout << LFsensor;
//	if (abs(LFsensor.value -RFsensor.value) < LIGHTSENSORJITTER)
//	cout << port1.value<<endl;
///////////	if ((port1.value & LFsensor != 0) && (port1.value & RFsensor !=0))
	LMotor.setdir(true);
	RMotor.setdir(true);
//	cout << (port1.value & LFsensor) << endl;
	
//	if (port1.value == 252)

	if (((port1.value & LFsensor) == 0) && ((port1.value & RFsensor) == 0))
	{
		cout << "Straight ahead" << endl;
		LMotor.setspeed(127);
		RMotor.setspeed(127);

	}
/////	if ((port1.value & LFsensor != 0) && (port1.value & RFsensor == 0))
//	if (port1.value==253)
	if (((port1.value & LFsensor) == 0) && ((port1.value & RFsensor) == 1))

	{
		cout << "Turn right" << endl;

		LMotor.setspeed(127);
		RMotor.setspeed(64);

	}
////////	if ((port1.value & RFsensor != 0 ) && (port1.value & LFsensor == 0))
//	if (port1.value==254)
	if (((port1.value & LFsensor) == 1) && ((port1.value & RFsensor) == 0))
	{
		cout << "Turn left" << endl;

		LMotor.setspeed(64);
		RMotor.setspeed(127);
	}
}
