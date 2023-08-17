
#include <Arduino.h>
#include <memory>
#include <iostream>

#include "TrainStation.h"
#include "MQTTServer.h"

std::unique_ptr<TrainStation> trainstation;
std::unique_ptr<MQTTServer> mqttServer;

void onConnectionEstablished()    //This function is called if the MQTTServer has an established connection with the wifi network
{
  trainstation->subscribeToTrain("TrainDemoSprint4");
}

void setup()
{
  Serial.begin(115200);

  mqttServer = std::unique_ptr<MQTTServer>(new MQTTServer()); //"JD", "VdE4fVR4EpMx"
  trainstation = std::unique_ptr<TrainStation>(new TrainStation(std::move(mqttServer)));
 
  trainstation->server->enableDebugMessages();
}

void loop()
{
  trainstation->server->run();
  bool newTrainInfo = trainstation->requestTrainInfo();
  if(newTrainInfo)
  {
    trainstation->ShowPlatformOccupation();
  }  
}