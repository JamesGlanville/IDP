#ifndef I2C_H
#define I2C_H

#include <iostream>
#include "comms.h"
using namespace std;

const int LFsensor = 1;
const int RFsensor = 2;

class i2c {
	request_instruction readname;
	command_instruction writename;
	int port;


public:
	i2c(int id);
	int value;
	void readall();
		void writeall();

};

extern i2c port1;

#endif
