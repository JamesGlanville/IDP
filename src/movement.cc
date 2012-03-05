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

void Movement::junctionToJunctionNew()
{
	LMotor.setdir(true);
  	RMotor.setdir(true);
  
  	//Move forward
  	LMotor.setspeed(127);
  	RMotor.setspeed(127);
  
  	while( /* On junction  */)
  	{
    	//Check off junction
  	}
  
	while(/* On Line */)
	{
		followLine();
		//Check if hit junction
	}

	LMotor.setspeed(0);
	RMotor.setspeed(0);
}
