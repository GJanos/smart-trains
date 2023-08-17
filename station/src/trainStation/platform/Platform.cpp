#include "Platform.h"

void Platform::AddExpectedTrain(TrainData::Train train)
{
    expectedTrain = train;

    //Print trainObj
    Serial.print("Train ID: ");
    Serial.println(expectedTrain.ID);

    Serial.println("Wagons:");
    for (const auto& wagonPair : expectedTrain.wagons) {
        const TrainData::Wagon& wagon = wagonPair.second;

        Serial.print("Wagon ID: ");
        Serial.println(wagon.ID);
        Serial.print("Length: ");
        Serial.println(wagon.length);
        Serial.print("Occupancy: ");
        Serial.println(wagon.occupationLevel);
        Serial.println();
    }
}


void Platform::AddPlatformLED(int pinRed, int pinGreen, int pinOrange)
{
    platformLEDs.push_back(std::unique_ptr<LED>(new RGBLED(pinRed, pinGreen, pinOrange)));
}

void Platform::ShowOccupation()
{
    //Check if the expectedTrain is empty
    //if so turn the platform leds off
    if(expectedTrain.wagons.empty())
    {
        //turn off the leds
        for(const auto& led : platformLEDs){         
            if(led != nullptr){
                led->turnOff();
            }            
        }
    }
    else{
        int currentWagonID = StandardHeadWagonID;   //Set the initial wagon ID to the standard headwagon ID
        int currentLEDRowLength = 1;                        
        bool error = false;

        for(const auto& led : platformLEDs)
        {
            //If there are no more wagons in the train turn off the remaining LEDs
            if(currentWagonID > (expectedTrain.wagons.size() + StandardHeadWagonID) || error)
            {
                led->turnOff();
            }
            else
            {
                Serial.print("WagonID : ");
                Serial.print(currentWagonID);
                Serial.println(" on");

                auto wagon = expectedTrain.wagons.find(currentWagonID);

                //If the wagon ID is not in the map of wagons or 
                if(wagon != expectedTrain.wagons.end()) 
                {
                    int color = expectedTrain.wagons[currentWagonID].occupationLevel;
                    led->turnOn(static_cast<LEDColor>(color));

                    //If the wagon Length equals the LEDrows on the platform, reset the LED row length and
                    //increment the currentWagonID
                    if(expectedTrain.wagons[currentWagonID].length == currentLEDRowLength){
                        currentWagonID++;
                        currentLEDRowLength = 1;
                    }
                    else{
                        //increment to go to the next row of LEDs
                        currentLEDRowLength++;
                    }
                }
                else{
                    led->turnOff();
                    error = true;
                }
            }            
        }
    }
}
