// *****************************************************************************
// *****************************************************************************
// SerialAdapter.cpp
//
// Author: Jason Tost
// Date:   11.23.2015
//
// *****************************************************************************
// *****************************************************************************

#include "Logger.h"
#include "Utility.h"
#include "SerialAdapter.h"

SerialAdapter::SerialAdapter(
   const String& id) : Adapter(id)
{
}

SerialAdapter::~SerialAdapter()
{
}

bool SerialAdapter::sendMessage(
   const Message& message)
{
   bool messageSent = false;

   String serializedMessage;

   if ((protocol != 0) &&
       (protocol->serialize(message, serializedMessage) == true))
   {
      Serial.print(serializedMessage);
      messageSent = true;
   }
   else
   {
      Logger::logDebug("Failed to serialize message " + toString(message.getMessageId()) + ".\n");
   }

   return (messageSent);
}

const Message* SerialAdapter::getMessage()
{
   Message* message = 0;

   if (Serial.available() > 0)
   {
      // Read from the serial connection.
      String string = Serial.readStringUntil('\n');

      // Parse the message.
      protocol->parse(string, message);

      if (message)
      {
         // Address from
         message->address(getId(), "");
      }
   }

   return (message);
}
