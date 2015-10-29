// *****************************************************************************
// *****************************************************************************
// Sensor.cpp
//
// Author: Jason Tost
// Date:   10.29.2015
//
// *****************************************************************************
// *****************************************************************************

#include "Sensor.h"

Sensor::Sensor(
   const String& sensorId,
   const int& pinId)
{
    this->sensorId = sensorId;
    this->pinId = pinId;
}

Sensor::~Sensor()
{

}

void Sensor::handleMessage(
   const Message* message)
{
   // No action.
}
