#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

#include "mechanism.h"

Mechanism mech;


void Mechanism::advanceTurntable()
{
	port2.value = port2.value | TURNMOT;
	delay(InitialAdvanceDelay);
	if((port2.value & TURNSWITCH) != 0)
	{
		port2.value = port2.value ^ TURNMOT;
	}
	
	if(turntablePosition!=5)
	{
		turntablePosition++;
	}
	else
	{
		turntablePosition = 1;
	}

}

void Mechanism::rotateTurntable(int select)
{
	//Keep rotating the turntable until it matches the select position
	while(select != turntablePosition)
	{
		advanceTurntable();
	}
}

void Mechanism::pullerOn()
{
	port1.value = port1.value | actuatorA; // Turn actuator on
	port1.writeall();
	delay(PullerOnDelay);
}

void Mechanism::pullerOff()
{
	port1.value = port1.value ^ actuatorA; //Turn actuator off
	port1.writeall();
	delay(PullerOffDelay);
}

void Mechanism::pusherOn()
{
	port1.value = port1.value | actuatorB; //Turn actuator on
	port1.writeall();
	delay(PusherOnDelay);
}

void Mechanism::pusherOff()
{
	port1.value = port1.value ^ actuatorB; //Turn actuator off
	port1.writeall();
	delay(PusherOffDelay);
}

int Mechanism::readMedalType()
{
	cout << "LDR value is:" << ldr.value << endl;
	if(ldr.value < LowerBoundLDR)
	{
		return 1;
	}
	else if(ldr.value > UpperBoundLDR)
	{
		return 3;
	}
	else{
		return 2;
	}
}

int Mechanism::collectMedal()
{
	
	while(!pressOpen)
	{
		if((port2.value & PRESSSWITCH)==0)
		{
			pressOpen = true;
		}
	}

	pullerOn();
	pullerOff();
	pullerOn();

	pullerOff();
	pullerOn();
	advanceTurntable();
	delay (500);
	pullerOff();

	return readMedalType();
}

void Mechanism::depositMedal(int medal)
{
	rotateTurntable(medal);
	pullerOn();
	pusherOn();
	pusherOff();
	pullerOff();
}

