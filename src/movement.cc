#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
#include "movement.h";

void Movement::followLine()
{
  if (((port1.value & LFsensor) == 0) && ((port1.value & RFsensor) == 0))
  {
    cout << "Straight ahead" << endl;
    LMotor.setspeed(127);
    RMotor.setspeed(127);
  }
  
  if (((port1.value & LFsensor) == 0) && ((port1.value & RFsensor) != 0))
  {
    cout << "Turn right" << endl;
    LMotor.setspeed(FASTSPEED);
    RMotor.setspeed(SLOWSPEED);
  }
  
  if (((port1.value & LFsensor) != 0) && ((port1.value & RFsensor) == 0))
  {
    cout << "Turn left" << endl;
    LMotor.setspeed(SLOWSPEED);
    RMotor.setspeed(FASTSPEED);
  }  
}

void Movement::junctionToJunction()
{
  LMotor.setdir(true);
	RMotor.setdir(true);
	if (traversingjunction) {cout << "traversing" << endl;}
//	cout << (port1.value & LFsensor) << (port1.value & RFsensor) << endl;
	

	if (((port1.value & LFsensor) == 0) && ((port1.value & RFsensor) == 0))
	{
		if (traversingjunction == true)
		{
			traversingjunction = false;
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