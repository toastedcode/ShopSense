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
}

void ButtonSensor::run()
{
   if (updateTimer.isExpired())
   {
      int reading = getPin()->read();

      if (reading != currentReading)
      {
         currentReading = reading;
      }

      updateTimer.restart();
   }
}

void ButtonSensor::handleMessage(
   const Message* message)
{
   Sensor::handleMessage(message);
}
