#ifndef I2C_H
#define I2C_H

#include <iostream>
#include "comms.h"
#include "config.h"
using namespace std;


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
