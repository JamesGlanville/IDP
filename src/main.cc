#include <iostream>
#include "comms.h"
#include "motors.h"
#include "i2c.h"
using namespace std;

int main ()

{
	//global Commlink Comms;
	if (Comms.init() != 0) {return -1;}
	Motor LMotor(1);
		LMotor.setdir(true);



	LMotor.setspeed(127);
	
	i2c port1(1);
	port1.value=255;
	port1.writeall();
	//sleep (1);
	while (1)
	{
	port1.readall();
		cout << port1.value << endl;
		//poll everything
		//decide if we need to jump to next state
		//decide based on state what to do
		//do it
	}
	return 0;
}

