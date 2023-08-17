#pragma once

#include <string>

class ServerConnection
{
public:
    virtual void publish(const std::string &topicName, const std::string &info) = 0;
    virtual bool subscribe(const std::string &topicName) = 0;
    virtual void unsubscribe(const std::string &topicName) = 0;
    virtual std::string returnMessage() = 0;

    virtual void enableDebugMessages() = 0;
    virtual void run() = 0;
    
};