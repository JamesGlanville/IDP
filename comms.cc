#include <iostream>
using namespace std;
#include <robot_instr.h>
#include <robot_link.h>
#include "comms.h"

#include <stopwatch.h>


#define ROBOT_NUM 24

Commlink Comms;


int Commlink::init ()
{
	
	stopwatch watch;
	#ifdef __arm__
	if (!rlink.initialise ()) { // setup for local hardware
	#else
	if (!rlink.initialise (ROBOT_NUM)) { // setup the link
	#endif

		cout << "Cannot initialise link" << endl;
		rlink.print_errs(" ");
		return -1;
	}
	watch.start();

	for (int i=0;i<1000;i++)
	{
		val = rlink.request (TEST_INSTRUCTION); // send test instruction
	}
	cout << watch.stop()<<endl;

	if (val == TEST_INSTRUCTION_RESULT)
	{
	cout << "Test passed" << endl;
	return 0; // all OK, finish
	}

	else if (val == REQUEST_ERROR) 
	{
		cout << "Fatal errors on link:" << endl;
		rlink.print_errs();
	}

	else
	{
	cout << "Test failed (bad value returned)" << endl;
	return -1; // error, finish
	}
	

}
