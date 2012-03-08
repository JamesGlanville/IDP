#include <iostream>
using namespace std;
#include "adc.h"

adc distancesense(distancepin); //Sets up the three ADC pins we need.
adc ldr(ldrpin);
adc thickness(thicknesspin);


adc::adc (int id) { //assigns ADC pins more neatly.
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

void adc::getvalue()
{
	value =  Comms.sendrequest(adc_id); //Populates value for the pin with the true value.
}

void adc::getvoltage()
{
	getvalue();
	voltage = (value/256.0)*5.0;
}
float adc::getdistance()
{
	float invdist;
	getvoltage();
	invdist = (voltage/3.0)*0.15;
	return 1.0/invdist;
}
