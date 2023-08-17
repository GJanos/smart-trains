#include "CanEvent.h"

CanEvent::CanEvent(CanEvents event, unsigned long eventLine, unsigned char eventLen, unsigned char eventMsg[8]) : event(event), eventLine(eventLine), eventLen(eventLen) {
    for (int i = 0; i < 8; i++)
    {
        this->eventMsg[i] = eventMsg[i];
    }
}

CanEvent::CanEvent() : event(CanEvents::No_Can_Msg), eventLine(0), eventLen(0), eventMsg("") {}

