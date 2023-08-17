#pragma once

#include "ButtonSensor.h"

class Seat 
{

public:
    Sensor* sensor;
    Seat();
    int OccupState();
};