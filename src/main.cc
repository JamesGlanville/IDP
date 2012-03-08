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

	Behaviour behaviour; //A load of init stuff gets called on this initialise.

	while (1)
	{
//		cout << "main loop" <<endl;
		behaviour.poll();
		behaviour.checkstate();
		behaviour.dostate();
	}
	return 0;
}

