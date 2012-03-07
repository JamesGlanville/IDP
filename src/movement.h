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
  private:
    void followLine();
    void followWall();
    void forward();
    void reverse();
    void stop();

  public:
    float position;
    void junctionToJunctionNew();
    void rotateOnJunction();
    void junctionToStand();
    void standToJunction();
    void pressSideToPodiumSide();
    
    
};

#endif
