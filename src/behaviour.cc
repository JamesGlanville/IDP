#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
#include "behaviour.h"

Behaviour::Behaviour() //init stuff
{
	//i2c port1(PORT1ADDR);
	//i2c port2(PORT2ADDR);
	port1.value= LFsensor | RFsensor; //set pins for input
	//port1.value=255; //Needs fixing from above.
	port1.writeall();
	LMotor.setramp(0);
	LMotor.setramp(0);
	state=1; //line follow
	port2.value=RELOAD|REMOVE|TURNMOT|BMEDAL|SMEDAL|GMEDAL; //pins 1 at start.
	
	
	//Testing new pcb, should be removed.
	int medals[5]={1,2,3,1,2};
	flashTypeLEDs();
	pressLED();
	

}

void Behaviour::poll()
{
	port1.readall();
	port2.readall();
//	cout << port1.value;

}

void Behaviour::checkstate()
{
    //Open state file for input and read state
    StateFile.open("state",ios::in);
    StateFile >> state; 
    StateFile.close();
}

void Behaviour::dostate()
{
    StateFile.open("state",ios::out);
    
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
		case 8:
			querymedals(); break;
		case 9:
			flashTypeLEDs();
	}
	StateFile << state;
	StateFile.close();
}

void Behaviour::pressLED()
{
	cout << "LEDLEDLEDLEDLED!" << endl;
	port2.value &= ~RELOAD;
	port2.writeall();
	delay(100);
	port2.value | RELOAD;
	port2.writeall();
	state++;
}

void Behaviour::junctionTojunction()
{
	LMotor.setdir(true);
	RMotor.setdir(true);
	if (traversingjunction) {cout << "traversing";}
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

void Behaviour::junctionTostand()
{
		//do stuff
		state++;
}
void Behaviour::collectMedal()
{
	int newmedaltype = 1; //always bronze for now to compile
		//do stuff
	for(int i=0;i<4;i++)
	{
		if (medals[i] == 0)
		{
			medals[i]=newmedaltype; break;
		}
	}
}
void Behaviour::standTojunction()
{
		//do stuff
		state++;

}
void Behaviour::querymedals()
{
	if (medals[4] != 0){state++;}
	else {state=4;}
}

void Behaviour::flashTypeLEDs()
{
		port2.value &= BMEDAL|SMEDAL|GMEDAL; //clears the 3 led bits.
		port2.writeall();
		for (int i=0;i<5; i++)
		{
			switch(medals[i])
			{
				case 1:
					port2.value &= ~BMEDAL; break;
				case 2:
					port2.value &= ~SMEDAL; break;
				case 3:
					port2.value &= ~GMEDAL;
			}
			port2.writeall();
			delay(MEDALLEDTIME);
			port2.value &= BMEDAL|SMEDAL|GMEDAL; //clears the 3 led bits.
			delay(500);
		}
		//do stuff
		state++;

}
