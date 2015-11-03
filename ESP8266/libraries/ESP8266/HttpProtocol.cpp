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
#include "Logger.h"
#include "PingMsg.h"
#include "SensorUpdateMsg.h"
#include "SetUpdateRateMsg.h"

bool HttpProtocol::parse(
   const String& string,
   Message* message)
{
   bool parsed = false;
   message = 0;

   Logger::logDebug("Parsing: " + string + "\n");

   String command = "";
   getParameter(string, "command", command);

   // PING
   // Format: command=ping&sensor_id=<sensor id>
   if (command == "ping")
   {
      String sensorId = "";

      if (getParameter(string, "sensor_id", sensorId))
      {
         message = new PingMsg();
         message->address(Message::SERVER_ID, sensorId);
         parsed = true;
      }
      else
      {
         Logger::logDebug("Bad message format: \"" + string + "\".\n");
      }
   }
   // SET_UPDATE_RATE
   // Format: command=set_update_rate&sensor_id=<sensor_id>&update_rate=<update rate>
   else if (command == "set_update_rate")
   {
      String sensorId = "";
      String updateRate = "";

      if (getParameter(string, "sensor_id", sensorId) &&
          getParameter(string, "updateRate", updateRate))

      {
         message = new SetUpdateRateMsg(updateRate.toInt());
         message->address(Message::SERVER_ID, sensorId);
         parsed = true;
      }
      else
      {
         Logger::logDebug("Bad message format: \"" + string + "\".\n");
      }
   }
   else
   {
      Logger::logDebug("Unsupported message: \"" + string + "\".\n");
   }

   return (parsed);
}

bool HttpProtocol::serialize(
   const Message& message,
   String& string)
{
   bool serialized = false;

   String messageId = message.getMessageId();

   // SENSOR_UPDATE
   // Format: command=data&sensor_id=<sensor id>&sensor_reading=<sensor reading>
   if (messageId == SensorUpdateMsg::getMessageId())
   {
     const SensorUpdateMsg* castMessage = static_cast<const SensorUpdateMsg*>(&message);

     if (castMessage == 0)
     {
        Logger::logDebug("Invalid message: \"" + message.getMessageId() + "\".\n");
     }
     else
     {

        string = "command=data&sensor_id=" +
                 castMessage->getSensorId() +
                 "&sensor_reading=" +
                 String(castMessage->getSensorReading());

        serialized = true;
     }
   }
   // PING
   // Format: command=ping&sensor_id=<sensor id>
   else if (messageId == PingMsg::getMessageId())
   {
      const PingMsg* castMessage = static_cast<const PingMsg*>(&message);

      if (castMessage == 0)
      {
         Logger::logDebug("Invalid message: \"" + message.getMessageId() + "\".\n");
      }
      else
      {

         string = "command=ping&sensor_id=" +
                  castMessage->getSource();

      }
   }
   else
   {
      Logger::logDebug("Unsupported message: \"" + message.getMessageId() + "\".\n");
   }

   return (serialized);
}


bool HttpProtocol::getParameter(
   const String& string,
   const String& parameterName,
   String& parameter) const
{
   const String PARAM_SEPERATOR = "&";

   int startPos = string.indexOf(parameterName);

   if (startPos != -1)
   {
      //
      // Get start and end positions of the parameter.
      // Format: parameterName=parameter&
      //
      startPos += parameterName.length() + 1;  // +1 for "=" sign.
      int endPos = string.indexOf(PARAM_SEPERATOR, startPos);

      if (endPos == -1)
      {
         endPos = string.length() - 1;
      }

      // Extract the parameter.
      parameter = string.substring(startPos, endPos);
   }
}
