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
#include "SetUpdateRateMsg.h"

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

   if (message.getMessageId() == SetUpdateRateMsg::getMessageId())
   {
      const SetUpdateRateMsg* castMessage = static_cast<const SetUpdateRateMsg*>(&message);

      Logger::logDebug("Setting update rate to " + String(castMessage->getUpdateRate()) + ".\n");

      setUpdateRate(castMessage->getUpdateRate());
   }

   return (handled);
}
