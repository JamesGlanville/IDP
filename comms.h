#ifndef COMMS_H
#define COMMS_H

#include <iostream>
using namespace std;
#include <robot_instr.h>
#include <robot_link.h>

#define ROBOT_NUM 24

class Commlink {
	robot_link rlink; // datatype for the robot link
	int val; // data from microprocessor
	int stat;

  public:
	void getstat();
    int init ();
    int sendcommand(command_instruction command,int param){return rlink.command(command, param);}
    int sendrequest(request_instruction command){return rlink.request(command);};
  } ;//Comms;


extern Commlink Comms;

#endif
