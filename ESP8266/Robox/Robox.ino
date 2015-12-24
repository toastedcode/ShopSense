// *****************************************************************************
// *****************************************************************************
// Robox.ino
//
// Author: Jason Tost
// Date:   11.30.2015
//
// *****************************************************************************
// *****************************************************************************

#include <WebServerAdapter.h>
#include <ESP8266.h>
#include <ESP8266WiFi.h>
#include <Logger.h>
#include <MessageHandler.h>
#include <MessageRouter.h>
#include <Motor.h>
#include <Timer.h>
#include <ToastBot.h>
#include <Utility.h>

// *****************************************************************************
//                               Global variables
// *****************************************************************************

Motor motor1("motor1", 5, 4);

Motor motor2("motor2", 3, 2);

// *****************************************************************************
//                               Arduino functions
// *****************************************************************************

void setup()
{
  Serial.begin(9600);
  
  ToastBot::getInstance()->begin();

  motor1.setup();

  motor2.setup();

  MessageRouter::getInstance()->registerHandler(motor1);
  MessageRouter::getInstance()->registerHandler(motor2);
}

void loop()
{
  ToastBot::getInstance()->run();

  motor1.run();

  motor2.run();
}
