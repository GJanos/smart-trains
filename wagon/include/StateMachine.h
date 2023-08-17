#ifndef ISTATEWAGON_H
#define ISTATEWAGON_H

#include "Wagon.h"
#include "CanEvent.h"

enum wagonState
{
    startup,
    waitingForHeadRespons,
    waitingForCommand,
    connectingWagons,
    gettingOccu
};

class StateMachine
{

public:
    StateMachine(Wagon *wagon);
    ~StateMachine();
    void handleEvent(CanEvent ev);

private:
    Wagon *wagon;
    wagonState currState;
    long Timer;
    int currWag;
    sendTrain::trainObj* currentTrain;
    
    wagonState handleStartupState(CanEvent ev);
    wagonState handleWaitingForHeadResponsState(CanEvent ev);
    wagonState handlewaitingForCommandState(CanEvent ev);
    wagonState handleconnectingWagonsState(CanEvent ev);
    wagonState handlegettingOccuState(CanEvent ev);
};
/* data */

#endif