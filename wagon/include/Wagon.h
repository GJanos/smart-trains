#ifndef WAGON_H
#define WAGON_H

#include <vector>
#include <string>

#include "MQTTServer.h"
#include "Seat.h"
#include "CanManager.h"
#include "Train.h"

enum OccupState
{
    EMPTY,
    NORMAL,
    FULL
};

class Wagon
{

public:
    Wagon(int trainID, int startID, int length, ServerConnection *server, CanManager *canManage, Seat *seats);
    Wagon(int trainID, int startID, int length, CanManager *canManage);
    ~Wagon();
    int getWagState(CanEvent ev);
    int getOccu(int currID);
    int newWagConn(CanEvent ev);
    void getHeadWag();
    int takeHeadWag();
    void wagDetach(int ID);
    void waitForCommand();
    void reset();
    int getStartId();
    void SetWagonIdFromHead(unsigned char eventMsg[]);
    //sendTrain::wagonObj convertWagonArrayToWagonObj(unsigned char *arr);
    sendTrain::wagonObj convertWagonArrayToWagonObj(unsigned char *arr);
    int getTrainId();
    int getWagonId();
    int getWagonLength();
    int getWagonOccup();
    ServerConnection* getServer();
    void publish(std::string serializedTrainObj);

private:
    int trainID;               // trains id
    int wagonID;               // wagons id inside the train
    int startID;               // wagons hard coded id
    int length;                // wagons length
    int wagonIDCounterForHead; // counter for the head to give out the corrent wagonIDs to the normal wagons
    long startTime;
    int currNumPass;
    int maxNumSeats;
    sendTrain::wagonObj* obj;
    int i = 0;
    // std::vector<Seat> seats;
    ServerConnection *server;
    CanManager *canManage;
    Seat *seats;
    OccupState occupState;
    void convertWagonIDToArray(unsigned char *arr, int num);
    int convertWagonIDToInt(unsigned char *arr);
};
#endif