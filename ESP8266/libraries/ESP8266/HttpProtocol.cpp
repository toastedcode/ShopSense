// *****************************************************************************
// *****************************************************************************
// HttpProtocol.cpp
//
// Author: Jason Tost
// Date:   10.27.2015
//
// *****************************************************************************
// *****************************************************************************

#include "HttpProtocol.h"
#include "SensorUpdateMsg.h"

HttpProtocol::HttpProtocol()
{
}

HttpProtocol::~HttpProtocol()
{
}

bool HttpProtocol::parse(
   const String& string,
   Message* message)
{
   return (false);
}

bool HttpProtocol::serialize(
   const Message* message,
   String& serializedMessage)
{
   bool serialized = true;

   String messageId = message->getMessageId();

   if (messageId == SensorUpdateMsg::getMessageId())
   {
     const SensorUpdateMsg* castMessage = static_cast<const SensorUpdateMsg*>(message);

     serializedMessage = "command=data&sensor_id=" +
                         castMessage->getSensorId() +
                         "&sensor_reading=" +
                         String(castMessage->getSensorReading());
   }
   else
   {
      bool serialized = false;
   }

   return (serialized);
}
