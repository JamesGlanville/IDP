#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
#include "behaviour.h"

Behaviour::Behaviour() //init stuff
{
	port1.value= LFsensor | RFsensor; //set pins for input
	//port1.value=255; //Needs fixing from above.
	port1.writeall();
	LMotor.setramp(0);
	LMotor.setramp(0);
	state=1; //Start state machine at beginning. (This should really load past state from file.)
	
//	port2.value=255;
//	port2.writeall();
	
	
	
	//All output pins high by default, inputs need to be set high before reads:
	port2.value=255;//RELOAD|REMOVE|TURNMOT|BMEDAL|SMEDAL|GMEDAL| TURNSWITCH|PRESSSWITCH; (same but longer)
	port2.writeall();
//	delay(1000000);
	
	
	//Testing new pcb, should be removed.
	medals[0]=1;
	medals[1]=2;
	medals[2]=3;
	medals[3]=1;
	medals[4]=2;
	flashTypeLEDs();
	pressLED();
	

}

void Behaviour::poll()
{
	port1.readall();
	port2.readall();
	distancesense.getvalue();
	ldr.getvalue();
	thickness.getvalue();
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
			flashTypeLEDs(); break;
		case 10:
			pressSideToPodiumSide(); break;
		case 11:
			junctionTojunction(); break;
		case 12:
			rotateOnJunction(LEFT); break;
			standtype++; //If we haven't been to a stand yet, set to 1
		case 13:
			junctionTostand(); break;
		case 14:
			depositMedal(); break;
		case 15:
			standTojunction(); break;
		case 16:
			removeLED(); break;
		case 17:
			isMedalTypeDone(); break;
		case 18:
			rotateOnJunction(RIGHT); break;
		case 19:
			areMedalsDone(); break;
		case 20:
			break; //We need to go back to the start box.
	}
	StateFile << state;
	StateFile.close();
}

void Behaviour::areMedalsDone()
{
	bool done=true;
	for (int i=0;i<5;i++)
	{
		if (medals[i] != 0) {done=false;}
	}
	if(done) {state++;} //Done with all the medals;
	else{state=11;} //Next stand.
}

void Behaviour::isMedalTypeDone()
{
	bool done=true;
	for (int i=0;i<5;i++)
	{
		if (medals[i] == standtype) {done=false;}
	}
	if(done) {state=18;} //Done all of that type.
	else {state=13;}
}

void Behaviour::rotateOnJunction(int dir)
{
	//Do something.
}
void Behaviour::pressSideToPodiumSide()
{
	//Do something.
}
void Behaviour::depositMedal()
{
	for(int i=0;i<5;i++)
	{
		if (medals[i] == standtype)
		{
			//Do something. Then set medals[i] to 0.
			//rotate,deliver medal.
			medals[i]=0;
		}
	}
}

void Behaviour::pressLED()
{
	cout << "Flashing press LED." << endl;
	port2.value &= ~RELOAD;
	port2.writeall();
	delay(100);
	port2.value | RELOAD;
	port2.writeall();
	state++;
}

void Behaviour::removeLED()
{
	cout << "Flashing remove LED." << endl;
	port2.value &= ~REMOVE;
	port2.writeall();
	delay(100);
	port2.value | REMOVE;
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
	for(int i=0;i<4;i++) //Finds lowest index to store new medal type in, when last one is filled new state will begin.
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
		port2.value |= BMEDAL|SMEDAL|GMEDAL; //clears the 3 led bits.
		port2.writeall();
		for (int i=0;i<5; i++)
		{
			switch(medals[i])
			{
				case 1:
					cout << "Flashing bronze LED." << endl;
					port2.value &= ~BMEDAL; break;
				case 2:
					cout << "Flashing silver LED." << endl;
					port2.value &= ~SMEDAL; break;
				case 3:
					cout << "Flashing gold LED." << endl;
					port2.value &= ~GMEDAL;
			}
			port2.writeall();
			delay(MEDALLEDTIME);
			port2.value |= BMEDAL|SMEDAL|GMEDAL; //clears the 3 led bits.
			delay(500);
		}
		state++;

}
