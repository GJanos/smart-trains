#pragma once

class Sensor
{
public:
    //Sensor(int buttonPin1, int buttonPin2);
    const int totalSeatsDown = 100;
    virtual void isPressed1() = 0;
    virtual void isPressed2() = 0;
    virtual float retPressCount() = 0;
};

class ButtonSensor : public Sensor
{
public:
    ButtonSensor(int buttonPin1, int buttonPin2);
    void isPressed1() override;
    void isPressed2() override;
    float retPressCount() override;
private:
    int buttonPin1;
    int buttonPin2;
    unsigned long lastDebounceTime1 = 0;
    const unsigned long debounceTimeInterval1 = 50;
    int prevButtonState1 = 0;
    unsigned long lastDebounceTime2 = 0;
    const unsigned long debounceTimeInterval2 = 50;
    int prevButtonState2 = 0;
    int pressCount = 0;
};