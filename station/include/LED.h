#pragma once

enum LEDColor{
    Green,
    Blue,
    Red
};

class LED
{
protected:
    int redPin = 0;
    int greenPin = 0;
    int bluePin = 0;
public:
    LED(int redPin, int greenPin, int bluePin){
        this->redPin = redPin;
        this->greenPin = greenPin;
        this->bluePin = bluePin;
    }

    virtual void turnOn(LEDColor color) = 0;
    virtual void turnOff() = 0;

    virtual int getRedPin() const = 0;
    virtual int getGreenPin() const = 0;
    virtual int getBluePin() const = 0;

};