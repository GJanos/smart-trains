#pragma once

#include <string>

class ServerConnection
{
public:
    virtual void publish(const std::string &info) = 0;
    virtual void subscribe(const std::string &topicName) = 0;
    virtual void run() =0;
};