#pragma once

#include <string>

#include "ServerConnection.h"
#include "EspMQTTClient.h"
#include "Train.h"
#include "TrainStation.h"


class MQTTServer : public ServerConnection
{
public:
    EspMQTTClient client;

    MQTTServer(const char* wifiSsid = "12connect", const char* wifiPassword = "", 
    const char* mqttServerIp = "test.mosquitto.org", const char* mqttUsername = "", const char* mqttPassword = "",
    const char* mqttClientName = "TestClient1", const short mqttServerPort = 1883);

    void publish(const std::string &topicName, const std::string &info) override;
    bool subscribe(const std::string &topicName) override;
    void unsubscribe(const std::string &topicName) override;
    std::string returnMessage() override;

    void enableDebugMessages() override;
    void run() override;

private:
    const std::string topicName;
    std::string convertedString;

    std::string mqttStringToCppString(const char* mqttString, size_t length);
};