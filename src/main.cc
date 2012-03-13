#include <iostream>
#include "comms.h"
#include "motors.h"
#include "i2c.h"
#include "adc.h"
#include "behaviour.h"
#include <cstdlib> 
using namespace std;

int main (int argc, char* argv[])
{
	if (argc == 2)
	{
		fstream initState;
		initState.open("state",ios::out);
		cout << "Manually starting at state: " << atoi(argv[1]) << endl;
		initState << atoi(argv[1]);
		initState.close();
	}
	
	
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

