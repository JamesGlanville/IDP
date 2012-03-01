#include <iostream>
using namespace std;
#include "i2c.h"

i2c port1(PORT1ADDR);
i2c port2(PORT2ADDR);

i2c::i2c (int id) {
	switch (id)
	{
		case 0:
			readname = READ_PORT_0;
			writename = WRITE_PORT_0; break;
		case 1:
			readname = READ_PORT_1;
			writename = WRITE_PORT_1; break;
		case 2:
			readname = READ_PORT_2;
			writename = WRITE_PORT_2; break;
		case 3:
			readname = READ_PORT_3;
			writename = WRITE_PORT_3; break;
		case 4:
			readname = READ_PORT_4;
			writename = WRITE_PORT_4; break;
		case 5:
			readname = READ_PORT_5;
			writename = WRITE_PORT_5; break;
		case 6:
			readname = READ_PORT_6;
			writename = WRITE_PORT_6; break;
		case 7:
			readname = READ_PORT_7;
			writename = WRITE_PORT_7;
			
	}
	
}

void i2c::readall() 
{
	value = Comms.sendrequest(readname);
}

void i2c::writeall() 
{
	//value = rlink.request (writename,value);
	Comms.sendcommand(writename, value);

}
