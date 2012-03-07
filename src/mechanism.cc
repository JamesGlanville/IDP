#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

#include "mechanism.h"

void advanceTurntable()
{
	//Do something with I2C
}

void rotateTurntable(int)
{
	//Do something else with I2C
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
	//Do something with ADC
	//Then decide type and return type int
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

