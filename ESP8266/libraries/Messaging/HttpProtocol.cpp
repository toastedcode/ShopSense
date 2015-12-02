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
#include "PingReplyMsg.h"
#include "ReadPinMsg.h"
#include "ReadPinReplyMsg.h"
#include "SensorUpdateMsg.h"
#include "SetUpdateRateMsg.h"
#include "Utility.h"
#include "VibrationSensorConfigMsg.h"
#include "WifiConfigMsg.h"
#include "WifiConfigReplyMsg.h"
#include "WritePinMsg.h"
#include "WritePinReplyMsg.h"

static const bool REQUIRED = true;
static const bool OPTIONAL = false;

static const String PING_REPLY_HTML = "<html><body><div>Ping reply from %s</div></body></html>";
static const String READ_PIN_REPLY_HTML = "<html><body><div>(%s) Read pin %d, value = %d</div></body></html>";
static const String WRITE_PIN_REPLY_HTML = "<html><body><div>(%s) Write pin %d, value = %d</div></body></html>";
static const String WIFI_CONFIG_REPLY_HTML = "<html><b>Wifi Setup</b></p><form method=\"get\" action=\"#\"><input type=\"hidden\" name=\"command\" value=\"wifi_config\"/><table><tr><td>SSID:</td><td><input type=\"text\" name=\"ssid\"/></td></tr><tr><td>Password:</td><td><input type=\"password\" name=\"password\"/></td></tr><tr><td><input type=\"submit\" value=\"Submit\"></td></tr></table></form></html>";

bool HttpProtocol::parse(
   const String& string,
   Message*& message)
{
   bool parsed = false;
   message = 0;

   Logger::logDebug("Parsing: " + string + "\n");

   String command = "";
   getParameter(string, "command", REQUIRED, command);

   Logger::logDebug("Parsed: " + command + "\n");

   // PING_MSG
   // Format: command=ping
   if (command == "ping")
   {
      message = new PingMsg();
      parsed = true;
   }
   // READ_PIN_MSG
   // Format: command=read&pin=<pin id>
   else if (command == "read")
   {
      String pinId = "";

      if (getParameter(string, "pin", REQUIRED, pinId))
      {
         message = new ReadPinMsg(pinId.toInt());
         parsed = true;
      }
      else
      {
         Logger::logDebug("Bad message format: \"" + string + "\".\n");
      }
   }
   // WRITE_PIN_MSG
   // Format: command=write&pin=<pin id>&value=<value>
   else if (command == "write")
   {
      String pinId = "";
      String value = "";

      if (getParameter(string, "pin", REQUIRED, pinId) &&
          getParameter(string, "value", REQUIRED, value))
      {
         message = new WritePinMsg(pinId.toInt(), value.toInt());
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

      if (getParameter(string, "sensor_id", REQUIRED, sensorId) &&
          getParameter(string, "updateRate", REQUIRED, updateRate))

      {
         message = new SetUpdateRateMsg(updateRate.toInt());
         parsed = true;
      }
      else
      {
         Logger::logDebug("Bad message format: \"" + string + "\".\n");
      }
   }
   // WIFI_CONFIG
   // Format: command=wifi_config&ssid=<ssid>&password=<password>
   else if (command == "wifi_config")
   {
      String ssid = "";
      String password = "";

      if (getParameter(string, "ssid", OPTIONAL, ssid) &&
          getParameter(string, "password", OPTIONAL, password))
      {
         message = new WifiConfigMsg(ssid, password);
         parsed = true;
      }
      else
      {
         Logger::logDebug("Bad message format: \"" + string + "\".\n");
      }
   }
   // VIBRATION_SENSOR_CONFIG
   // Format: command=vibration_sensor_config&server_ip=&sensitivity=&responsiveness=&update_rate=&is_enabled=
   else if (command == "vibration_sensor_config")
   {
      String serverIpAddress = "";
      String sensitivity =  "";
      String responsiveness = "";
      String updateRate = "";
      String isEnabled = "";

      if (getParameter(string, "server_ip_address", OPTIONAL, serverIpAddress) &&
          getParameter(string, "sensitivity", OPTIONAL, sensitivity) &&
          getParameter(string, "responsiveness", OPTIONAL, responsiveness) &&
          getParameter(string, "update_rate", OPTIONAL, updateRate) &&
          getParameter(string, "is_enabled", OPTIONAL, isEnabled))
      {
         message = new VibrationSensorConfigMsg(serverIpAddress,
                                                sensitivity.toInt(),
                                                responsiveness.toInt(),
                                                updateRate.toInt(),
                                                ((isEnabled == "true") ? true : false));
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
   // PING_REPLY
   else if (messageId == PingReplyMsg::getMessageId())
   {
      const PingReplyMsg* castMessage = static_cast<const PingReplyMsg*>(&message);

      if (castMessage == 0)
      {
         Logger::logDebug("Invalid message: \"" + message.getMessageId() + "\".\n");
      }
      else
      {
         char buffer[256];
         sprintf(buffer, PING_REPLY_HTML.c_str(), castMessage->getIpAddress().c_str());

         string = httpReply(String(buffer));

         serialized = true;
      }
   }
   // READ_PIN_REPLY_MSG
   else if (messageId == ReadPinReplyMsg::getMessageId())
   {
      const ReadPinReplyMsg* castMessage = static_cast<const ReadPinReplyMsg*>(&message);

      if (castMessage == 0)
      {
         Logger::logDebug("Invalid message: \"" + message.getMessageId() + "\".\n");
      }
      else
      {
         char buffer[256];
         sprintf(buffer,
                 READ_PIN_REPLY_HTML.c_str(),
                 (castMessage->getSuccess() == true) ? "SUCCESS" : "FAILED",
                 castMessage->getPin(),
                 castMessage->getValue());

         string = httpReply(String(buffer));

         serialized = true;
      }
   }
   // WRITE_PIN_REPLY_MSG
   else if (messageId == WritePinReplyMsg::getMessageId())
   {
      const WritePinReplyMsg* castMessage = static_cast<const WritePinReplyMsg*>(&message);

      if (castMessage == 0)
      {
         Logger::logDebug("Invalid message: \"" + message.getMessageId() + "\".\n");
      }
      else
      {
         char buffer[256];
         sprintf(buffer,
                 WRITE_PIN_REPLY_HTML.c_str(),
                 (castMessage->getSuccess() == true) ? "SUCCESS" : "FAILED",
                 castMessage->getPin(),
                 castMessage->getValue());

         string = httpReply(String(buffer));

         serialized = true;
      }
   }
   // WIFI_CONFIG_REPLY_MSG
   else if (messageId == WifiConfigReplyMsg::getMessageId())
   {
      const WifiConfigReplyMsg* castMessage = static_cast<const WifiConfigReplyMsg*>(&message);

      if (castMessage == 0)
      {
         Logger::logDebug("Invalid message: \"" + message.getMessageId() + "\".\n");
      }
      else
      {
         char buffer[512];
         sprintf(buffer,
                 WIFI_CONFIG_REPLY_HTML.c_str());

         string = httpReply(String(buffer));

         serialized = true;
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
   const bool& isRequired,
   String& parameter) const
{
   const String PARAM_SEPERATORS = "& ";
   const String SPACE = " ";

   bool success = !isRequired;

   int startPos = string.indexOf(parameterName);

   if (startPos != -1)
   {
      //
      // Get start and end positions of the parameter.
      // Format: parameterName=parameter&
      //
      startPos += parameterName.length() + 1;  // +1 for "=" sign.
      int endPos = Utility::findFirstOf(string, PARAM_SEPERATORS, startPos);

      if (endPos == -1)
      {
         endPos = string.length() - 1;
      }

      // Extract the parameter.
      parameter = string.substring(startPos, endPos);

      // Record our success.
      success |= true;
   }

   return (success);
}

String HttpProtocol::httpReply(
   const String& content)
{
   String str;

   str += "HTTP/1.1 200 OK\r\n";
   str += "Content-Type: text/html\r\n\r\n";
   str += "<!DOCTYPE HTML>";
   str += content;

   return (str);
}
