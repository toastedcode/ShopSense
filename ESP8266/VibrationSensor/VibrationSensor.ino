// *****************************************************************************
// *****************************************************************************
// VibrationSensor.ino
//
// Author: Jason Tost
// Date:   12.1.2015
//
// *****************************************************************************
// *****************************************************************************

#include <WebServerAdapter.h>
#include <ESP8266.h>
#include <ESP8266WiFi.h>
#include <Logger.h>
#include <MessageHandler.h>
#include <MessageRouter.h>
#include <Timer.h>
#include <ToastBot.h>
#include <Utility.h>
#include <VibrationSensor.h>

// *****************************************************************************
//                               Global variables
// *****************************************************************************

VibrationSensor sensor("VIBRATION_SENSOR", 14);

// *****************************************************************************
//                               Arduino functions
// *****************************************************************************

void setup()
{
  Serial.begin(9600);
  
  ToastBot::getInstance()->begin();

  sensor.setup();

  MessageRouter::getInstance()->registerHandler(sensor);
}

void loop()
{
  ToastBot::getInstance()->run();

  sensor.run();
}
