#include "ButtonSensor.h"
#include "Arduino.h"

ButtonSensor::ButtonSensor(int buttonPin1, int buttonPin2) : buttonPin1(buttonPin1), buttonPin2(buttonPin2)
{

}

void ButtonSensor::isPressed1()
{
    if ((millis() - lastDebounceTime1) > debounceTimeInterval1)
    {
        // Serial.println("TEMPUPBUTTON");
        int buttonState = digitalRead(buttonPin1);
        if (buttonState != prevButtonState1)
        {
            prevButtonState1 = buttonState;
            if (buttonState == LOW)
            {
                if (pressCount < totalSeatsDown)
                {
                    if (pressCount < 100)
                    {
                        pressCount += 10;    
                        Serial.println(pressCount);
                    }       
                }
            }
            lastDebounceTime1 = millis();
        }
    }
}

void ButtonSensor::isPressed2()
{
    if ((millis() - lastDebounceTime2) > debounceTimeInterval2)
    {
        // Serial.println("TEMPUPBUTTON");
        int buttonState = digitalRead(buttonPin2);
        if (buttonState != prevButtonState2)
        {
            prevButtonState2 = buttonState;
            if (buttonState == LOW)
            {
                if (pressCount <= totalSeatsDown)
                {
                    if (pressCount > 0)
                    {
                        pressCount -= 10;    
                        Serial.println(pressCount);
                    }             
                }
            }
            lastDebounceTime2 = millis();
        }
    }
}

float ButtonSensor::retPressCount()
{
    return pressCount;
}