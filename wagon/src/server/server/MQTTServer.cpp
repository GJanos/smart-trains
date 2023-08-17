#include "MQTTServer.h"
#include "EspMQTTClient.h"
#include <string>
#include <vector>
#include <stdlib.h>

MQTTServer::MQTTServer() : client(
                               "OnePlus 9",          //12connect
                               "hoihoi12",                   //
                               "test.mosquitto.org", // MQTT Broker server ip ()
                               "",                   // Can be omitted if not needed
                               "",                   // Can be omitted if not needed
                               "ESP32WERKHOER",        // Client name that uniquely identify your device
                               1883                  // The MQTT port, default to 1883. this line can be omitted
                           )
{
    topicName = "TrainDemoSprint4";
    client.enableDebuggingMessages();
    client.loop();
}

MQTTServer::MQTTServer(const char *wifiSsid, const char *wifiPassword,
                       const char *mqttServerIp, const char *mqttUsername, const char *mqttPassword,
                       const char *mqttClientName, const short mqttServerPort, const char topicName) : client(wifiSsid,       //12connect
                                                                                        wifiPassword,   //
                                                                                        mqttServerIp,   // MQTT Broker server ip ()
                                                                                        mqttUsername,   // Can be omitted if not needed
                                                                                        mqttPassword,   // Can be omitted if not needed
                                                                                        mqttClientName, // Client name that uniquely identify your device
                                                                                        mqttServerPort  // The MQTT port, default to 1883. this line can be omitted
                                                                                 )
{
    this->topicName = topicName;
}

void MQTTServer::onConnectionEstablished(){
    Serial.println("krijg kinder ziektes");
}
void MQTTServer::publish(const std::string &info)
{
    // String topic(topicName.c_str());
    // String payload(info.c_str());
    // client.publish(topic, payload);
    Serial.println(client.publish(String(topicName.c_str()), String(info.c_str())));
}

void MQTTServer::subscribe(const std::string &topicName)
{
    this->topicName = topicName;
}

void MQTTServer::run(){
    client.loop();
    client.enableDebuggingMessages();
}
