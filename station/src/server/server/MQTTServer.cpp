#include "MQTTServer.h"
#include "EspMQTTClient.h"


MQTTServer::MQTTServer(const char* wifiSsid, const char* wifiPassword, 
const char* mqttServerIp, const char* mqttUsername, const char* mqttPassword,
const char* mqttClientName, const short mqttServerPort) : client(
    wifiSsid,           //12connect
    wifiPassword,       //
    mqttServerIp,       // MQTT Broker server ip ()
    mqttUsername,       // Can be omitted if not needed
    mqttPassword,       // Can be omitted if not needed
    mqttClientName,     // Client name that uniquely identify your device
    mqttServerPort      // The MQTT port, default to 1883. this line can be omitted
)
{
}

void MQTTServer::publish(const std::string &topicName, const std::string &info)
{
    String topic(topicName.c_str());
    String payload(info.c_str());
    client.publish(topic, payload);
}

bool MQTTServer::subscribe(const std::string &topicName)
{
    String topic(topicName.c_str());
    bool succes = client.subscribe(topic, [&](const String & payload)
    {
         convertedString = mqttStringToCppString(payload.c_str(), payload.length());
    });    
    return succes;
}

void MQTTServer::unsubscribe(const std::string &topicName)
{
  String topic(topicName.c_str());
  client.unsubscribe(topic);
}

void MQTTServer::enableDebugMessages()
{
    client.enableDebuggingMessages();
}

void MQTTServer::run()
{
    client.loop();
}

std::string MQTTServer::returnMessage()
{
    return convertedString;
}

std::string MQTTServer::mqttStringToCppString(const char* mqttString, size_t length) {
    // Create a C++ string object and copy the bytes from the MQTT string
    std::string cppString(mqttString, length);
    return cppString;    
}