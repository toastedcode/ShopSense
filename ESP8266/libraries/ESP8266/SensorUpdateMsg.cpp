// *****************************************************************************
// *****************************************************************************
// SensorUpdateMsg.cpp
//
// Author: Jason Tost
// Date:   10.29.2015
//
// *****************************************************************************
// *****************************************************************************

#include "SensorUpdateMsg.h"

SensorUpdateMsg::SensorUpdateMsg(
   const String& sourceId,
   const String& destinationId,
   const int& sensorReading) : Message(getMessageId(), sourceId, destinationId)
{
   this->sensorReading = sensorReading;
}

SensorUpdateMsg::~SensorUpdateMsg()
{
}
