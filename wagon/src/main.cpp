#include <Arduino.h>
#include <SPI.h>
#include <mcp_can.h>

#include "MQTTServer.h"
#include "StateMachine.h"
#include "Seat.h"

const int spiCSPin = 5;

ServerConnection *serverConn;
// std::unique_ptr<MQTTServer> mqttServer;
// current
MCP_CAN *can;
CanManager *canMan;
Wagon *wagon;
Seat *seats;
StateMachine *wagonStateMachine;
long TIME = 0;
int ret;

void onConnectionEstablished(){
    Serial.println("krijg kinder ziektes");
}

void setup()
{
  Serial.begin(115200);
  // mqttServer = std::unique_ptr<MQTTServer>(new MQTTServer());
  can = new MCP_CAN(spiCSPin);
  while (CAN_OK != can->begin(MCP_ANY, CAN_500KBPS, MCP_16MHZ))
  {
    Serial.println("CAN BUS Init Failed");
    delay(100);
  }
  Serial.println("CAN BUS  Init OK!");
  can->setMode(MCP_NORMAL);
  canMan = new CanManager(can);
  serverConn = new MQTTServer();
  seats = new Seat();
  // station = new D_TrainStation(serverConn);
  wagon = new Wagon(1, 3, 1, serverConn, canMan, seats);
  wagonStateMachine = new StateMachine(wagon);
// 
  
}

void loop()
{
  // Serial.println(wagon->getStartId());
  // Serial.println(time + 100 < millis());
  //wagon->getServer()->client.loop();
  seats->sensor->isPressed1();
  seats->sensor->isPressed2();
  //ret = seats->OccupState();
  //serverConn->client.loop();
  // mqttServer->client.loop();
  if (TIME + 100 < millis())
  {

    TIME = millis();
    CanEvent ev = canMan->readCanMsg();
    wagonStateMachine->handleEvent(ev);
    /* code */
  }
}
