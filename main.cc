#include <iostream>
#include "comms.h"
using namespace std;

int main ()

{
	//global Commlink Comms;
	if (Comms.init() != 0) {return -1;}
	
	while (0)
	{
		//poll everything
		//decide if we need to jump to next state
		//decide based on state what to do
		//do it
	}	
	return 0;
}

