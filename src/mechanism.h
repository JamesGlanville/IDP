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
		void pusherOn();
		void pusherOff();
		void pullerOn();
		void pullerOff();
	public:
		int collectMedal();
		int readMedalType();
		
		void depositMedal(int medal);
};

extern Mechanism mech;

#endif
