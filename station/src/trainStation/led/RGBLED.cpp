#include "RGBLED.h"

RGBLED::RGBLED(int redPin, int greenPin, int bluePin) : 
    LED(redPin, greenPin, bluePin)
{
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
}

void RGBLED::turnOn(LEDColor color)
{
    switch(color)
    {
    case Green:
        digitalWrite(greenPin, HIGH);
        digitalWrite(bluePin, LOW);
        digitalWrite(redPin, LOW);
        break;

    case Blue:
        digitalWrite(greenPin, LOW);
        digitalWrite(bluePin, HIGH);
        digitalWrite(redPin, LOW);
        break;

    case Red:
        digitalWrite(greenPin, LOW);
        digitalWrite(bluePin, LOW);
        digitalWrite(redPin, HIGH);
        break;
    default:
        digitalWrite(greenPin, LOW)
        digitalWrite(bluePin, LOW);
        digitalWrite(redPin, LOW);
        break;
    }
}

void RGBLED::turnOff()
{
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
    digitalWrite(redPin, LOW);
}

int RGBLED::getRedPin() const
{
    return LED::redPin;
}

int RGBLED::getGreenPin() const
{
    return LED::greenPin;
}

int RGBLED::getBluePin() const
{
    return LED::bluePin;
}


