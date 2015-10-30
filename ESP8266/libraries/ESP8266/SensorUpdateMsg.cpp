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
   const String& sensorId,
   const int& sensorReading) : Message(getMessageId())
{
   this->sensorId = sensorId;
   this->sensorReading = sensorReading;
}

SensorUpdateMsg::~SensorUpdateMsg()
{
}
