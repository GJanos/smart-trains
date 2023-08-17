#include "StateMachine.h"

#define TIMEOUT_UNIT 1000
#define TIMEOUT_CONNECTING_WAGONS 5000

StateMachine::StateMachine(Wagon *wagon) : wagon(wagon), currState(startup), Timer(0)
{
    currentTrain = new sendTrain::trainObj(wagon->getTrainId());
    // currentTrain.trainID = wagon->getTrainId();
    currWag = 6;
}

StateMachine::~StateMachine()
{
    delete wagon;
}

void StateMachine::handleEvent(CanEvent ev)
{

    Serial.print("CURRSTAE: ");
    Serial.println( currState);
    switch (currState)
    {
    case startup:
        currState = handleStartupState(ev);
        break;
    case waitingForHeadRespons: // Change to sendRequestToHeadState name to be more clear
        currState = handleWaitingForHeadResponsState(ev);
        break;
    case waitingForCommand:
        Serial.println("in waitingForCommand");
        currState = handlewaitingForCommandState(ev);
        break;
    case connectingWagons:
        Serial.println("In connectingWagons");
        currState = handleconnectingWagonsState(ev);
        break;
    case gettingOccu:
        currState = handlegettingOccuState(ev);
        break;
    default:

        break;
    }
}
wagonState StateMachine::handleStartupState(CanEvent ev)
{
    Timer = millis();
    return waitingForHeadRespons;
}
wagonState StateMachine::handleWaitingForHeadResponsState(CanEvent ev)
{
    wagonState nextState;
    
    switch (ev.event)
    {
    case CanEvents::Head_Occu_Req:
        Timer = millis();
        nextState = waitingForHeadRespons;
        break;
    case CanEvents::Head_Wagid_Recieve:
        Timer = millis();

        if (wagon->getStartId()  == ev.eventMsg[0])
        {
            wagon->SetWagonIdFromHead(ev.eventMsg);
            Serial.println("HELLO");
            nextState = waitingForCommand;
            /* code */
        } else {
            nextState = waitingForHeadRespons;
            Serial.print("HELLO4:");
        }
        break;
    default:
        wagon->getHeadWag();
        if (Timer + (wagon->getStartId() * TIMEOUT_UNIT * 6) < millis())
        {
            Serial.println("In take head funciont");
            wagon->takeHeadWag(); // TODO: make it do something
            nextState = connectingWagons;
            Timer = millis();
            break;
        }
        nextState = waitingForHeadRespons;

        break;
    }
    return nextState;
}

wagonState StateMachine::handlewaitingForCommandState(CanEvent ev)
{
    wagonState nextState;
    wagon->waitForCommand();
    switch (ev.event)
    {
    case CanEvents::Head_Occu_Req:
        wagon->getWagState(ev);
        nextState = waitingForCommand;
        Timer = millis();
        break;
    default:
        if (Timer + (wagon->getStartId() * 1000 * 10) < millis())
        {
            // wagon->takeHeadWag();
            nextState = waitingForHeadRespons;
            Timer = millis();
            break;
        }
        nextState = waitingForCommand;
        break;
    }
    return nextState;
}

wagonState StateMachine::handleconnectingWagonsState(CanEvent ev)
{
  wagon->getServer()->run();
    wagonState nextState;
    switch (ev.event)
    {
    case CanEvents::Wagon_Wagid_Req:
        // Serial.println("NEW WAGON NEEDED");
        wagon->newWagConn(ev); // First char will be hardcoded id to make sure the correct wagon will get the id in the wagon
        nextState = connectingWagons;
        break;
    default:
        if (Timer + (TIMEOUT_CONNECTING_WAGONS) < millis())
        {
            nextState = gettingOccu;
            currentTrain->wagonInfos.emplace_back(wagon->getWagonId(), wagon->getWagonOccup(), wagon->getWagonLength());
            Timer = millis();
            break;
        }
        nextState = connectingWagons;
        break;
    }
    return nextState;
}
wagonState StateMachine::handlegettingOccuState(CanEvent ev)
{
    wagonState nextState;
    // int retVal = 0;
  wagon->getServer()->run();

    switch (ev.event)
    {
    case CanEvents::Wagon_Occup_Resp:
    {
        Serial.print("Got Message ");
        Serial.println(ev.eventMsg[1]);
        sendTrain::wagonObj obj = wagon->convertWagonArrayToWagonObj(ev.eventMsg);
        currentTrain->wagonInfos.emplace_back(obj);
        currWag++;
        nextState = gettingOccu;
        break;
        }
    default:
    int retVal = 0;
    if (Timer + (TIMEOUT_UNIT /2) < millis())
    {
        retVal = wagon->getOccu(currWag);
    }
        if (retVal == -1)
        {
            //All wagons should be saved
            currWag = 6;
            nextState = connectingWagons; /* code */
            // Serial.println(currentTrain.c_str());
            std::string message = sendTrain::serialize(currentTrain);
            wagon->publish(message);
            Serial.println("GOT ALL WAGONS");
            currentTrain->wagonInfos.clear();
            break;
        }

        if (Timer + (TIMEOUT_UNIT) < millis())
        {
            currWag++;
            Timer = millis();
        }
        nextState = gettingOccu;
        break;
    }
    return nextState;
}
