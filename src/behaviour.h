#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

#include <iostream>
#include <delay.h>

#include <fstream>
#include "comms.h"
#include "motors.h"
#include "adc.h"
#include "i2c.h"
#include "config.h"
#include "mechanism.h"

class Behaviour {
private:
	bool traversingjunction;
	int medals[5]; //1 - bronze, 2-silver, 3-gold, 0 - empty
	void querymedals();
	void flashTypeLEDs();
	friend class Movement;
	void areMedalsDone();
	void isMedalTypeDone();
  public:
	void followWall(int linestocross);
	void findline (int dir,int delaytime);
	void advance(bool dir,int time,int speed);
	void stop();
	void swapsides();
	void getToCentre(); //If we're on a line, advance to the axis of rotation is on the cross.

	int ramp;
	int standtype; //Which stand are we at? 0 if we're not.
	int state;
	fstream StateFile;
	void poll();
	void checkstate();
	void dostate();
	void junctionTojunction(bool dir);
	void flashLED(int LED);
	void junctionTostand(); // RACE CONDITION - speed being changed multiple times
							//so actual speed will vary depending on how long stuff takes.
							// FIX.
	void collectMedal();
	void standTojunction(); 
	//void pressSideToPodiumSide(); //Deprecated.
	void rotateOnJunction(int dir,int delay); 
	void depositMedal();
	Behaviour();

};

#endif
