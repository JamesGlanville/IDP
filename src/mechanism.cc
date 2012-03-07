#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

#include "mechanism.h"

Mechanism mech();


void advanceTurntable()
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

void rotateTurntable(int select)
{
	//Keep rotating the turntable until it matches the select position
	while(select != turntablePosition)
	{
		advanceTurntable();
	}
}

void Mechanism::raiseClaw()
{
	port1.value = port1.value | actuatorA; // Turn actuator on
	port1.writeall();
	delay(RaiseClawDelay);
}

void Mechanism::lowerClaw()
{
	port1.value = port1.value ^ actuatorA; //Turn actuator off
	port1.writeall();
	delay(LowerClawDelay);
}

void Mechanism::advanceGripper()
{
	port1.value = port1.value | actuatorB //Turn actuator on
	port1.writeall();
	delay(AdvanceGripperDelay);
}

void Mechanism::retractClaw()
{
	port1.value = port1.value ^ actuatorB //Turn actuator off
	port1.writeall();
	delay(RetractGripperDelay();
}

int Mechanism::readMedalType()
{
	if(ldr.value < LowerBoundLDR)
	{
		int type = 0;
	}
	else if(ldr.value > UpperBoundLDR)
	{
		int type = 2;
	}
	else{
		int type = 1;
	}
}

int Mechanism::collectMedal()
{
	advanceTurntable();
	
	while(!pressOpen)
	{
		if((port2.value & PRESSSWITCH)==0)
		{
			pressOpen = true;
		}
	}

	raiseClaw();
	advanceGripper();
	lowerClaw();
	retractGripper();

	return readMedalType();
}

void Mechanism::depositMedal(int medal)
{
	rotateTurntable(medal);
	advanceGripper();
	retractGripper();
}

