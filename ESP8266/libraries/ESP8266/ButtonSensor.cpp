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
   const String& id,
   const int& pinId) : Sensor(id, pinId)
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

      if (reading != currentReading)
      {
         currentReading = reading;

        // Send an update to the server.
        SensorUpdateMsg message(getId(), currentReading);
        message.address(getId(), Message::SERVER_ID);
        MessageRouter::getInstance()->sendMessage(message);
      }

      updateTimer.start();
   }
}

bool ButtonSensor::handleMessage(
   const Message& message)
{
   return (Sensor::handleMessage(message));
}
