#pragma once

#include "LED.h"
#include "Arduino.h"

class RGBLED : public LED
{
private:
public:
    RGBLED(int redPin, int greenPin, int bluePin);

    void turnOn(LEDColor color) override;
    void turnOff() override;

    int getRedPin() const override;
    int getGreenPin() const override;
    int getBluePin() const override;
};