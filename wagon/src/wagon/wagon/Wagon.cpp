#include <Arduino.h>
#include <cstring>
#include <cstdio>

#include "Wagon.h"
// #include <CanManager.h>

#define HEAD_TIMEOUT 3000

Wagon::Wagon(int trainID, int startID, int length, ServerConnection *server, CanManager *canManage, Seat *seats) : trainID(trainID), startID(startID), length(length), server(server), canManage(canManage), seats(seats)
{
    // wagonState = WagonState::NORMAL;
    // nCurrState = normalState::STARTUP;
    wagonID = 0x5; // Should we keep only one of these variables for incrementation and make the head wagon ID defined
    wagonIDCounterForHead = 0x6;
    occupState = EMPTY;
}

Wagon::Wagon(int trainID, int startID, int length, CanManager *canManage) : trainID(trainID), startID(startID), length(length), canManage(canManage)
{
    // wagonState = WagonState::NORMAL;
    // nCurrState = normalState::STARTUP;
    wagonID = 0x5; // Should we keep only one of these variables for incrementation and make the head wagon ID defined
    wagonIDCounterForHead = 0x6;
    occupState = EMPTY;
}

Wagon::~Wagon()
{
    // delete trainStation;
    delete canManage;
}



void Wagon::convertWagonIDToArray(unsigned char *arr, int num)
{
    memset(arr, '0', 7);
    arr[7] = '\0';
    int temp = num;
    for (int i = 6; i >= 0; i--)
    {
        arr[i] = (temp % 10) + '0';
        temp /= 10;
    }
}

sendTrain::wagonObj Wagon::convertWagonArrayToWagonObj(unsigned char *arr)
{
    sendTrain::wagonObj* obj = new sendTrain::wagonObj(arr[0], arr[1], arr[2]);
    // obj.wagonID = arr[0]; //std::atoi(arr[0]);
    // obj.occup = arr[1];   //std::atoi(arr[1]);
    // obj.length = arr[2];  //std::atoi(arr[2]);

    return *obj;
}

int Wagon::convertWagonIDToInt(unsigned char *arr)
{
    int result = 0;
    for (int i = 0; i < 7; i++)
    {
        if (arr[i] >= '0' && arr[i] <= '9')
        {
            result = result * 10 + (arr[i] - '0');
        }
    }

    return result;
}

void Wagon::getHeadWag()
{
    unsigned char buff[8] = " N->H 2";
    buff[0] = startID;

    CanEvent msg = CanEvent(CanEvents::Wagon_Wagid_Req, 0x02, 8, buff);
    canManage->writeCanMsg(msg);
}

void Wagon::SetWagonIdFromHead(unsigned char eventMsg[])
{
    wagonID = eventMsg[1];
}

// int Wagon::handleGetMsgState()
// {
//     // here put a time based of loop for 1 sec
//     if (millis() - startTime < 5000)
//     {
//         // Serial.println("In head");
//         if (CAN_MSGAVAIL == CAN->checkReceive())
//         {
//             unsigned char len = 0;
//             unsigned char buf[8];
//             unsigned long rxId;
//             // CAN->readMsgBuf(&rxId, &len, buf);
//             readCanMsg(buff, &rxId);

//             Serial.print("Data from ID: 0x");
//             Serial.println(rxId, HEX);
//             Serial.println("Head Get Message State");
//             if (rxId == 0x02)
//             {

//                 unsigned char nextIDForNormalWag[8];
//                 convertWagonIDToArray(nextIDForNormalWag, wagonIDCounterForHead);
//                 // nextIDForNormalWag[0] = (char) 3;
//                 Serial.println(wagonIDCounterForHead);
//                 nextIDForNormalWag[0] = (wagonIDCounterForHead % 10) + 48;
//                 // CAN->sendMsgBuf(0x01, 0, 8, nextIDForNormalWag);
//                 sendCanMsg(setId, 0x01);
//                 // wagonIDCounterForHead++;
//             }
//         }
//     }
//     else
//     {
//         // every second it goes there
//         startTime = millis();
//         /////////////////////////////hCurrState = headState::GETOCCU;
//     }
// }

// int Wagon::getNumPass()
// {
//     return 0;
// }

int Wagon::getWagState(CanEvent ev)
{
    if (ev.eventMsg[0] == wagonID)
    {
        getWagonOccup();
        unsigned char buff[8];
        buff[0] = wagonID;
        buff[1] = occupState;
        buff[2] = length;
        CanEvent msg = CanEvent(CanEvents::Head_Occu_Req, 0x04, 8, buff);
        canManage->writeCanMsg(msg);
    }

    return 0;
}

int Wagon::getOccu(int currID)
{
    if (currID >= wagonIDCounterForHead)
    {
        return -1;
    }

    unsigned char buff[8];

    buff[0] = currID;
    CanEvent msg = CanEvent(CanEvents::Head_Occu_Req, 0x03, 8, buff);
    canManage->writeCanMsg(msg);
    return 0;
}

// void Wagon::pingWagons(int wagonID)
// {
// }

int Wagon::newWagConn(CanEvent ev)
{
    unsigned char buff[8];
    // convertWagonIDToArray(buff, wagonIDCounterForHead++);
    buff[0] = ev.eventMsg[0];
    buff[1] = wagonIDCounterForHead++;
    CanEvent msg = CanEvent(CanEvents::Head_Wagid_Recieve, 0x01, 8, buff);
    canManage->writeCanMsg(msg);
    return 0;
}

int Wagon::takeHeadWag()
{
    unsigned char buff[8] = "newHead";
    CanEvent newCan(CanEvents::Head_Wagid_Recieve, 0x03, 8, buff);
    canManage->writeCanMsg(newCan);
    Serial.println("HELLO2");
    return 0;
}

void Wagon::wagDetach(int ID)
{
}

// std::string Wagon::getAllWagsState()
// {
//     return std::string();
// }

void Wagon::waitForCommand()
{
}

void Wagon::reset()
{
}

ServerConnection* Wagon::getServer(){
    return server;
}

int Wagon::getStartId()
{
    return startID;
}

int Wagon::getTrainId()
{
    return trainID;
}

int Wagon::getWagonId()
{
    return wagonID;
}

int Wagon::getWagonLength()
{
    return length;
}

int Wagon::getWagonOccup()
{
    if ((seats->OccupState() >= 0) && (seats->OccupState() <= 50))
    {
        occupState = EMPTY;
    }
    else if ((seats->OccupState() > 50) && (seats->OccupState() <= 85))
    {
        occupState = NORMAL;
    }
    else
    {
        occupState = FULL;
    }
    return occupState;
}

void Wagon::publish(std::string serializedTrainObj)
{
    server->publish(serializedTrainObj);
}
