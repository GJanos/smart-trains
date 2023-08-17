#ifndef CAN_MANAGER_H
#define CAN_MANAGER_H

#include <mcp_can.h>
#include "CanEvent.h"

class CanManager
{
public:
    CanManager(MCP_CAN *CAN);
    ~CanManager();
    CanEvent readCanMsg();
    void writeCanMsg(CanEvent msg);

private:
    MCP_CAN* CAN;
};

#endif