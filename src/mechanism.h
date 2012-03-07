#ifndef MECHANISM_H
#define MECHANISM_H

#include <iostream>
#include <delay.h>
#include <fstream>

#include "comms.h"
#include "motors.h"
#include "adc.h"
#include "i2c.h"
#include "config.h"

class Mechanism
{
	private:
		int turntablePosition;
		bool pressOpen;

		void advanceTurntable();
		void rotateTurntable(int medal);
		void raiseClaw();
		void lowerClaw();
		void AdvanceGripper();
		void retractGripper();
		void readMedalType();

	public:
		int collectMedal();

		void depositMedal(int medal);
}

