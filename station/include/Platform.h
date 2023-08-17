#pragma once

#include <vector>
#include <memory>

#include "RGBLED.h"
#include "Train.h"

#define StandardHeadWagonID 5

class Platform
{
public:
    int platformNr;

    Platform(int PlatformNr = 1){
        platformNr = PlatformNr;
    }
    
    void AddExpectedTrain(TrainData::Train train);
    void AddPlatformLED(int pinRed, int pinGreen, int pinOrange);
    void ShowOccupation();
    
private:
    std::vector<std::unique_ptr<LED>> platformLEDs;
    TrainData::Train expectedTrain;
};