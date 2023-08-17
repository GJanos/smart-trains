#pragma once

#include <vector>
#include <string>

#include "Platform.h"
#include "MQTTServer.h"
#include "Train.h"

#include <map>

class TrainStation
{
public:
    std::unique_ptr<ServerConnection> server;

    TrainStation(std::unique_ptr<ServerConnection> server = nullptr);

    bool subscribeToTrain(const std::string &topicName);
    bool requestTrainInfo(); 
    void ShowPlatformOccupation();

private:
    std::string previousJsonString;
    Platform platform;
};