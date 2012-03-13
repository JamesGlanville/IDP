#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
#include "behaviour.h"
#include "mechanism.h"
#include <stopwatch.h>

Behaviour::Behaviour() //init stuff
{
	Comms.sendcommand(RAMP_TIME,RAMPT);	
	//state=1; (We load past state from file now)

	for (int i; i<5; i++) {medals[i]=0;} // I think this is pointless.
	traversingjunction = false; // likewise.
}

void Behaviour::poll()
{
	port1.value|= LFsensor|RFsensor|LMsensor|RMsensor|bumperA|bumperB; //set pins for input
	port2.value=255;//RELOAD|REMOVE|TURNMOT|BMEDAL|SMEDAL|GMEDAL| TURNSWITCH|PRESSSWITCH; (same but longer)
	port1.writeall();
	port2.writeall();
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
    cout << "State: " << state << "  ";
	switch (state)
	{
/*		case 1: //Getting to press, junctionTojunction x3
			junctionTojunction(true); break;
		case 2:		
			junctionTojunction(true); break;
		case 3:
			junctionTojunction(true); break;	*/
		case 1:
			followWall(1); break;
		case 2:
			advance(FORWARDS,100,30);	//forwards for 100ms at 30, so findline isn't already
										//on a line
		case 3:
			findline(RIGHT); break;
		case 4: //PressLED
			flashLED(RELOAD); break;
		case 5:
			junctionTostand(); break;
		case 6:
			collectMedal(); break;
		case 7:
			standTojunction(); break;
		case 8:
			querymedals();  break;
		case 9:
			flashTypeLEDs(); break;
		case 10:
			swapsides(); break;
//			pressSideToPodiumSide(); break;
		case 11:
			junctionTojunction(true); break;
		case 12:
			rotateOnJunction(LEFT); break;
			standtype++; //If we haven't been to a stand yet, set to 1
		case 13:
			junctionTostand(); break;
		case 14:
			depositMedal(); break;
		case 15:
			standTojunction(); break; //really just backwards junct2junct
		case 16:
			removeLED(); break;
		case 17:
			isMedalTypeDone(); break;
		case 18:
			rotateOnJunction(RIGHT); break;
		case 19:
			areMedalsDone(); /*break;
		case 20:
			break; *///We need to go back to the start box.
	}
	StateFile << state;
	StateFile.close();
}

void Behaviour::advance(bool dir,int time,int speed)
{
	LMotor.setdir(dir)
	RMotor.setdir(dir)
	LMotor.setspeed(speed);
	RMotor.setspeed(speed);
	if (time == 0) { return;} // 0 means we don't stop
	delay(time);
	LMotor.setspeed(0);
	RMotor.setspeed(0);	
}

void Behaviour::swapsides()
{
	advance(FORWARDS,200,50);	//200ms at 50, want to tweak this so
								//findline gets to be roughly pointing 
								//at the middle of the side wall.
	findline(LEFT);
	advance(FORWARDS,0,FASTSPEED);
	while (distancesense.getdistance() >= 15.0)
	{
		poll();
	}
	followWall(0); // traverse side wall, stop when we touch the line.

	LMotor.setspeed(0);
	RMotor.setspeed(FASTSPEED);
	delay(3000);
	stop();
	state++;
}

void Behaviour::stop();
{
	LMotor.setspeed(0);
	RMotor.setspeed(0);		
}	

void Behaviour::findline(RIGHT)
{
	if (dir == LEFT)
	{
		LMotor.setdir(false);	LMotor.setspeed(FASTSPEED);
		RMotor.setdir(true);	RMotor.setspeed(FASTSPEED);
	}
	else
	{
		LMotor.setdir(true);	LMotor.setspeed(FASTSPEED);
		RMotor.setdir(false);	RMotor.setspeed(FASTSPEED);
	}	
	if (dir == LEFT)
	{
		while ((port1.value & LFsensor) == 0)
		{
			poll();
		}
		while ((port1.value & LFsensor) != 0)
		{
			LMotor.setspeed(SLOWSPEED);
			RMotor.setspeed(SLOWSPEED);
			poll();
		}	
	}
	if (dir == RIGHT)
	{
		while ((port1.value & RFsensor) == 0)
		{
			poll();
		}
		while ((port1.value & RFsensor) != 0)
		{
			LMotor.setspeed(SLOWSPEED);
			RMotor.setspeed(SLOWSPEED);
			poll();
		}	
	}
	stop();
	state++;
	
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

void Behaviour::rotateOnJunction(int dir) // We need to move forward first
		//This should really be split into a "findJunctionCenter" and then a
		//findline, which in itself should take as an argument a delay.
{
	stop(); // Pretty sure we don't need this.
	LMotor.setdir(true);
	RMotor.setdir(true);
	delay(3000);
	while ((((port1.value & LMsensor) == 0) || ((port1.value & RMsensor) == 0)))
	{
		if (((port1.value & LFsensor) == 0) && ((port1.value & RFsensor) == 0))
		{	
			cout << "Straight aheadRRRR" << endl;
			LMotor.setspeed(127);
			RMotor.setspeed(127);
		}
		if (((port1.value & LFsensor) == 0) && ((port1.value & RFsensor) != 0))
		{
			cout << "Turn rightRRRR" << endl;
			LMotor.setspeed(SLOWSPEED);
			RMotor.setspeed(FASTSPEED);
		}
		if (((port1.value & LFsensor) != 0) && ((port1.value & RFsensor) == 0))
		{
			cout << "Turn leftRRRR" << endl;
			LMotor.setspeed(FASTSPEED);
			RMotor.setspeed(SLOWSPEED);
		}	
		
		poll();
	}
	cout << "l:" << (port1.value & LMsensor) << "r:" << (port1.value & RMsensor) << endl;
	//delay(3000);
	if (dir == LEFT)
	{
		LMotor.setdir(false);
		LMotor.setspeed(FASTSPEED);
		RMotor.setdir(true);
		RMotor.setspeed(FASTSPEED);
	}
	else
	{
		LMotor.setdir(true);
		LMotor.setspeed(FASTSPEED);
		RMotor.setdir(false);
		RMotor.setspeed(FASTSPEED);
	}	
	delay(TURNWAIT);
	if (dir == LEFT)
	{
		while ((port1.value & LFsensor) == 0)
		{
			poll();
		}
		while ((port1.value & LFsensor) != 0)
		{
			poll();
		}	
	}
	if (dir == RIGHT)
	{
		while ((port1.value & RFsensor) == 0)
		{
			poll();
		}
		while ((port1.value & RFsensor) != 0)
		{
			poll();
		}	
	}
	LMotor.setdir(true);
	LMotor.setspeed(0);
	RMotor.setdir(true);
	RMotor.setspeed(0);
	state++;

}
void Behaviour::pressSideToPodiumSide() // DEPRECATED in favour of swapsides.
{
	LMotor.setdir(true);
	RMotor.setdir(true);
	LMotor.setspeed(FASTSPEED);
	RMotor.setspeed(FASTSPEED);
	delay(1000);
	rotateOnJunction(LEFT);
	//We should now be on the curved line, pointing slightly to the wall.
///	here's a float: distance.getdistance();
	LMotor.setdir(true);
	RMotor.setdir(true);
	LMotor.setspeed(FASTSPEED);
	RMotor.setspeed(FASTSPEED);
	delay(2000);
	
	while(((port1.value & LFsensor)==0) && ((port1.value & RFsensor)==0))
	{
		RMotor.setspeed(92);
		
		if (distancesense.getdistance() >= SIDECLEARANCE)
		{
			LMotor.setspeed(FASTSPEED);
		}
		else
		{
			LMotor.setspeed(SLOWSPEED);
		}
		poll();
	}
	

	LMotor.setspeed(0);
	RMotor.setspeed(FASTSPEED);
	delay(3000);
	LMotor.setspeed(0);
	RMotor.setspeed(0);		
	state++;	// Hopefully we're in a good enough position to just trust 
					// junctionTojunction to work. Ideally we want to change
					// the use here of TURNWAIT to a value where we are going
					// as parallel as possible to the line, but will hit it 
					// a bit before we need to do anything, so junctiontojunction
					// will straighten up. This probably won't work as written here.
	
	
}

void Behaviour::followWall(int linestocross)
{
	stopwatch watch;

	int msToWait = 3000; // We'll wait at least 1s (?) before using light sensor readings.
	LMotor.setdir(true);
	RMotor.setdir(true);
	
	while(linestocross > -1)
	{
		RMotor.setspeed(92);
		
		if (distancesense.getdistance() >= 15.0)
		{
			LMotor.setspeed(FASTSPEED);
		}
		else
		{
			LMotor.setspeed(SLOWSPEED);
		}
		
		if ((port1.value & LFsensor) != 0 )
		{
			if (watch.read <= msToWait)
			{
				//watch.start();
				cout << "Repeated reading." << endl;
			}
			else
			{
				linestocross--;
				watch.start();
			}
			
		}
		poll();
	}
	
	stop();	
	state++;	
}
void Behaviour::depositMedal()
{
	for(int i=0;i<5;i++)
	{
		if (medals[i] == standtype)
		{
			mech.depositMedal(i);
			medals[i]=0;
		}
	}
}

void Behaviour::flashLED(int LED)
{
	cout << "Flashing LED: " << LED << endl;
	port2.value &= ~LED;
	port2.writeall();
	delay(100);
	port2.value |= LED;
	port2.writeall();
	delay(5000);
	state++;
}

void Behaviour::junctionTojunction(bool dir)
{
	if(ramp>=RAMPLESS){ramp-=RAMPLESS;} // every time this gets called, we'll ramp a bit less.
	LMotor.setdir(dir);
	RMotor.setdir(dir);
	if (traversingjunction) {cout << "traversing";}
//	cout << (port1.value & LFsensor) << (port1.value & RFsensor) << endl;
	

	if (((port1.value & LFsensor) == 0) && ((port1.value & RFsensor) == 0))
	{
		if (traversingjunction == true)
		{
			traversingjunction = false;
			state++;
			ramp = RAMPT; //get back to normal ramping for next function.
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
		//delay(200);
		traversingjunction = true;		
	}
	Comms.sendcommand(RAMP_TIME,ramp);

}

void Behaviour::junctionTostand()
{
	bool atStand = false;
	LMotor.setdir(true);
	RMotor.setdir(true);

	RMotor.setspeed(FASTSPEED);
	LMotor.setspeed(FASTSPEED);

	cout << "Approaching Stand" << endl;

	if(((port1.value & bumperA) != 0) && ((port1.value & bumperB) != 0))
	{
		cout << "At Stand" << endl;
		stop();
		state++;
		return;
	}
	if (((port1.value & LFsensor) == 0) && ((port1.value & RFsensor) == 0))
	{
		cout << "Straight ahead" << endl;
		LMotor.setspeed(FASTSPEED);
		RMotor.setspeed(FASTSPEED);
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
void Behaviour::collectMedal()
{
	for(int i=0;i<5;i++) //Finds lowest index to store new medal type in, when last one is filled new state will begin.
	{
		if (medals[i] == 0)
		{
			medals[i]=mech.collectMedal(); break;
		}
	}
	cout << "Medals collected: " << medals[0] << " " << medals[1] << " " << medals[2] << " " << medals[3] << " " << medals[4] << endl;
	state++;
}
void Behaviour::standTojunction()
{
	junctionTojunction(false);		
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
