// *****************************************************************************
// *****************************************************************************
// DweetProtocol.cpp
//
// Author: Jason Tost
// Date:   12.23.2015
//
// *****************************************************************************
// *****************************************************************************

#include "DweetProtocol.h"
#include "Logger.h"
#include "Messages.h"

bool DweetProtocol::parse(
   const String& string,
   Message*& message)
{
   bool parsed = false;

   return (parsed);
}

bool DweetProtocol::serialize(
   const Message& message,
   String& string)
{
   bool serialized = false;

   MessageId messageId = message.getMessageId();

   // SENSOR_UPDATE
   // Format: https://dweet.io/dweet/for/my-thing-name?state=<state>&stateTime=<stateTime>
   if (messageId == SensorUpdateMsg::MESSAGE_ID)
   {
     const SensorUpdateMsg* castMessage = static_cast<const SensorUpdateMsg*>(&message);

     if (castMessage == 0)
     {
        Logger::logDebug("Invalid message: \"" + toString(message.getMessageId()) + "\".\n");
     }
     else
     {
        const String DWEET_STRING = "/dweet/for/%s?state=%d&stateTime=%d";

        char buffer[256];
        sprintf(buffer,
                DWEET_STRING.c_str(),
                castMessage->getSource().c_str(),
                castMessage->getSensorReading(),
                castMessage->getSensorReadingTime());

        string = String(buffer);

        serialized = true;
     }
   }
   else
   {
      Logger::logDebug("Unsupported message: \"" + toString(message.getMessageId()) + "\".\n");
   }

   return (serialized);
}
