// *****************************************************************************
// *****************************************************************************
// ButtonSensor.cpp
//
// Author: Jason Tost
// Date:   10.29.2015
//
// *****************************************************************************
// *****************************************************************************

#include "ButtonSensor.h"
#include "MessageRouter.h"
#include "SensorUpdateMsg.h"

ButtonSensor::ButtonSensor(
   const String& sensorId,
   const int& pinId) : Sensor(sensorId, pinId)
{
}

ButtonSensor::~ButtonSensor()
{
}

void ButtonSensor::setup()
{
   updateTimer.start();
}

void ButtonSensor::run()
{
   if (updateTimer.isExpired())
   {
      int reading = getPin()->read();

      //if (reading != currentReading)
      {
         currentReading = reading;

        // Send an update to the server.
        SensorUpdateMsg message(sensorId, currentReading);
        message.address(sensorId, MessageRouter::SERVER_ID);
        MessageRouter::sendMessage(&message);
      }

      updateTimer.start();
   }
}

void ButtonSensor::handleMessage(
   const Message* message)
{
   Sensor::handleMessage(message);
}
