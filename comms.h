#include <iostream>
using namespace std;
#include <robot_instr.h>
#include <robot_link.h>

#define ROBOT_NUM 24

class Commlink {
	robot_link rlink; // datatype for the robot link
	int val; // data from microprocessor

  public:
    int init ();
  } ;//Comms;

