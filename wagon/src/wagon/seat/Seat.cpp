#include "Seat.h"

Seat::Seat()
{
    sensor = new ButtonSensor(12, 13);
}

int Seat::OccupState()
{
    // sensor->isPressed1();
    // sensor->isPressed2();
    int occup = (sensor->retPressCount() / sensor->totalSeatsDown) * 100;
    return occup;
}