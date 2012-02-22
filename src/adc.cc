#include <iostream>
using namespace std;
#include "adc.h"

//Lmotor = motor1, Rmotor = motor2 
//Motor LMotor(1);


adc::adc (int id) {
	switch (id)
	{
		case 0:
			adc_id = ADC0; break;
		case 1:
			adc_id = ADC1; break;
		case 2:
			adc_id = ADC2; break;
		case 3:
			adc_id = ADC3; break;
		case 4:
			adc_id = ADC4; break;
		case 5:
			adc_id = ADC5; break;
		case 6:
			adc_id = ADC6; break;
		case 7:
			adc_id = ADC7; break;
	}
	
}

int adc::getvalue()
{
	return Comms.sendrequest(adc_id);
}