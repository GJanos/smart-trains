#pragma once

#include <string>

#include "ServerConnection.h"
#include "EspMQTTClient.h"

class MQTTServer : public ServerConnection
{
public:
    void onConnectionEstablished();
    EspMQTTClient client;
    MQTTServer();
    MQTTServer(const char *wifiSsid, const char *wifiPassword, const char *mqttServerIp, const char *mqttUsername, const char *mqttPassword, const char *mqttClientName, const short mqttServerPort, const char topicName);
    void publish(const std::string &info) override;
    void subscribe(const std::string &topicName) override;
    void run() override;

private:
    std::string topicName;
};