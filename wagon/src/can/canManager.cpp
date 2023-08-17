#include "CanManager.h"

CanManager::CanManager(MCP_CAN *CAN) : CAN(CAN) {}

CanManager::~CanManager(){
    delete CAN;
}

CanEvent CanManager::readCanMsg()
{
    CanEvent event;

    if (CAN_MSGAVAIL == CAN->checkReceive())
    {
        CAN->readMsgBuf(&event.eventLine, &event.eventLen, event.eventMsg);

        switch (event.eventLine)
        {
        case 0x01:
            event.event = CanEvents::Head_Wagid_Recieve;
            break;
        case 0x02:
            event.event = CanEvents::Wagon_Wagid_Req;
            break;
        case 0x03:
            event.event = CanEvents::Head_Occu_Req;
            break;
        case 0x04:
            event.event = CanEvents::Wagon_Occup_Resp;
            break;
        }
    }
    return event;
}

void CanManager::writeCanMsg(CanEvent msg)
{
    CAN->sendMsgBuf(msg.eventLine, 0, msg.eventLen, msg.eventMsg);
    Serial.print("WRITING CAN MSG: ");
    for (size_t i = 0; i < 8; i++)
    {
        Serial.print(" ");
        Serial.print(msg.eventMsg[i]);
    }
    Serial.println();
}