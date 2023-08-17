#ifndef CAN_EVENT_H
#define CAN_EVENT_H

enum class CanEvents
{
    No_Can_Msg,
    Head_Wagid_Recieve,
    Wagon_Wagid_Req,
    Head_Occu_Req,
    Wagon_Occup_Resp,
    Head_Disc_Timeout,
    Head_Comm_Timeout,
    Head_Occup_Timeout
};

class CanEvent
{
public:
    CanEvents event;
    unsigned long eventLine;
    unsigned char eventLen;
    unsigned char eventMsg[8];

    CanEvent();
    CanEvent(CanEvents event, unsigned long eventLine, unsigned char eventLen, unsigned char eventMsg[8]);
};

#endif