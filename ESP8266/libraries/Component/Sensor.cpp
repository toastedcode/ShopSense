// *****************************************************************************
// *****************************************************************************
// Sensor.cpp
//
// Author: Jason Tost
// Date:   10.29.2015
//
// *****************************************************************************
// *****************************************************************************

#include "Logger.h"
#include "Sensor.h"

Sensor::Sensor(
   const String& id,
   const int& pinId) : MessageHandler(id)
{
    this->pinId = pinId;
}

Sensor::~Sensor()
{
}

bool Sensor::handleMessage(
   const Message& message)
{
   bool handled = false;

   return (handled);
}
