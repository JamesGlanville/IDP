#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <iostream>
#include <delay.h>

#include "comms.h"
#include "motors.h"
#include "adc.h"
#include "i2c.h"
#include "config.h"

class Movement {

  public:
    float position;
    void junctionToJunction();
    
};

#endif