#ifndef ADC_H
#define ADC_H

#include <iostream>
#include "comms.h"
#include "config.h"
using namespace std;


class adc {
	request_instruction adc_id;
  public:
	int value;
	float voltage;
    adc (int id);
	void getvalue();
	void getvoltage();
	float getdistance();
};

extern adc distancesense;
extern adc ldr;
extern adc thickness;


#endif
