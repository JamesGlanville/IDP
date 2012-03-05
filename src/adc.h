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
    adc (int id);
	void getvalue();
};

extern adc distance;
extern adc ldr;
extern adc thickness;


#endif
