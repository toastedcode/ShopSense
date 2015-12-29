// *****************************************************************************
// *****************************************************************************
// VibrationSensor.ino
//
// Author: Jason Tost
// Date:   12.1.2015
//
// *****************************************************************************
// *****************************************************************************

#include <DweetProtocol.h>
#include <ESP8266.h>
#include <ESP8266WiFi.h>
#include <Logger.h>
#include <MessageHandler.h>
#include <MessageRouter.h>
#include <Timer.h>
#include <ToastBot.h>
#include <Utility.h>
#include <VibrationSensor.h>
#include <VibrationSensor2.h>
#include <WebClientAdapter.h>
#include <WebServerAdapter.h>

// *****************************************************************************
//                               Global variables
// *****************************************************************************

const String DWEET_SERVER_ADDRESS = "dweet.io";

VibrationSensor2 sensor("pptp_machine01_vibration", 14);

DweetProtocol dweetProtocol;

WebClientAdapter dweetAdapter(DWEET_SERVER_ADDRESS);

// *****************************************************************************
//                               Arduino functions
// *****************************************************************************

void setup()
{
  Serial.begin(9600);
  
  ToastBot::getInstance()->begin();

  sensor.setup();

  sensor.setServerId(DWEET_SERVER_ADDRESS);

  MessageRouter::getInstance()->registerHandler(sensor);

  dweetAdapter.setProtocol(dweetProtocol);
  dweetAdapter.setServerAddress(DWEET_SERVER_ADDRESS);
  MessageRouter::getInstance()->registerAdapter(dweetAdapter);
}

void loop()
{
  ToastBot::getInstance()->run();

  sensor.run();
}
