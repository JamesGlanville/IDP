#include <iostream>
#include "comms.h"
#include "motors.h"
#include "i2c.h"
#include "adc.h"
#include "behaviour.h"
using namespace std;


int main ()

{
	if (Comms.init() != 0) {return -1;}

	Behaviour behaviour;
	
	behaviour.state=5; //line follow
	
	i2c port1(7);
	port1.value=255;
	port1.writeall();
	port1.readall();
	cout << port1.value;
	while (1)
	{
		behaviour.poll();
		behaviour.checkstate();
		behaviour.dostate();
	}
	return 0;
}

