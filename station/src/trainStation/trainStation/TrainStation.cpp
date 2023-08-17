#include "TrainStation.h"

TrainStation::TrainStation(std::unique_ptr<ServerConnection> server) : server(std::move(server)) 
{
  platform.AddPlatformLED(15,2,0);
  platform.AddPlatformLED(17,16,4);
  platform.AddPlatformLED(19,18,5);
  platform.AddPlatformLED(23,21,22);
  platform.AddPlatformLED(32,33,25);
}

bool TrainStation::subscribeToTrain(const std::string &topicName)
{
    return server->subscribe(topicName); 
}

bool TrainStation::requestTrainInfo()
{
    bool newString = false;
    std::string jsonString = server->returnMessage();
    if((jsonString != "") && (previousJsonString != jsonString))
    {
        TrainData::Train* train = TrainData::deserializeTrain(jsonString);

        if(train != nullptr)
        {
            platform.AddExpectedTrain(*train);
            delete train;
        }        

        newString = true;
    }
    
    previousJsonString = jsonString;
    return newString;
}

void TrainStation::ShowPlatformOccupation()
{
    platform.ShowOccupation();
}