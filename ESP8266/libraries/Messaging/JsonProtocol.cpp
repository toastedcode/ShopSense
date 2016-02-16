// *****************************************************************************
// *****************************************************************************
// JsonProtocol.cpp
//
// Author: Jason Tost
// Date:   2.15.2016
//
// *****************************************************************************
// *****************************************************************************

#include "JsonProtocol.h"
#include "Logger.h"
#include "Messages.h"
#include "Utility.h"

StaticJsonBuffer<200> JsonProtocol::jsonBuffer;

bool JsonProtocol::parse(
   const String& string,
   Message*& message)
{
   bool parsed = false;
   message = 0;

   Logger::logDebug("Parsing: " + string + "\n");

   // Parse the string into the JSON tree.
   JsonObject& json = jsonBuffer.parseObject(string.c_str());

   if ((json.success()) &&
       (json.containsKey("command")))
   {
      String command = json.get("command");

      // PING_MSG
      // Format: {"command":"ping"}
      if (command == "ping")
      {
         message = new PingMsg();
         parsed = true;
      }
      // SET_LOGGING_MSG
      // Format: {"command":"logging", "loggingEnabled":"true"}
      else if (command == "logging")
      {
         bool loggingEnabled = json.get("loggingEnabled");

         if (json.containsKey("loggingEnabled"))
         {
            message = new SetLoggingMsg(loggingEnabled);
            parsed = true;
         }
         else
         {
            Logger::logDebug("Bad message format: \"" + string + "\".\n");
         }
      }
      // WIFI_CONFIG
      // Format: {"command":"wifi_config", "ssid":"<ssid>", "password":"<password>"}
      else if (command == "wifi_config")
      {
         String ssid = "";
         String password = "";

         if ((json.containsKey("ssid")) &&
             (json.containsKey("password")))
         {
            message = new WifiConfigMsg(json.get("ssid"), json.get("password"));
            parsed = true;
         }
         else
         {
            Logger::logDebug("Bad message format: \"" + string + "\".\n");
         }
      }
      // VIBRATION_SENSOR_CONFIG
      // Format: {"command":"vibration_sensor_config",
      //          "sensitivity":"<sensitivity>",
      //          "responsiveness":"<responsiveness>",
      //          "update_rate":"<update_rate>",
      //          "is_enabled":"<is_enabled>"}
      else if (command == "vibration_sensor_config")
      {
         String sensorId = "";
         String serverIpAddress = "";
         String sensitivity =  "0";
         String responsiveness = "0";
         String updateRate = "";
         String isEnabled = "";

         if ((json.containsKey("sensitivity")) &&
             (json.containsKey("responsiveness")) &&
             (json.containsKey("update_rate")) &&
             (json.containsKey("is_enabled")))
         {
            message = new VibrationSensorConfigMsg("sensorId",  // TODO
                                                   json.get("sensitivity"),
                                                   json.get("responsiveness"),
                                                   json.get("update_rate"),
                                                   json.get("is_enabled"));
            parsed = true;
         }
         else
         {
            Logger::logDebug("Bad message format: \"" + string + "\".\n");
         }
      }
      // MOTOR_CONFIG
      // Format: {"command":"motor_config", "speed":"<speed>"}
      else if (command == "motor_config")
      {
         String speed = "";

         if (json.containsKey("speed"))
         {
            int speed = json.get("speed");
            message = new MotorConfigMsg(speed);
            parsed = true;
         }
         else
         {
            Logger::logDebug("Bad message format: \"" + string + "\".\n");
         }
      }

      if (message)
      {
         // Address to the component, if specified.
         //message->address("", component);
      }
      else
      {
         Logger::logDebug("Unsupported message: \"" + command + "\".\n");
      }
   }

   return (parsed);
}

bool JsonProtocol::serialize(
   const Message& message,
   String& string)
{
   bool serialized = false;

   MessageId messageId = message.getMessageId();

   // SENSOR_UPDATE
   // Format: {"command":"data", "sensor_reading":"<sensor_reading>"}
   if (messageId == SensorUpdateMsg::MESSAGE_ID)
   {
     const SensorUpdateMsg* castMessage = static_cast<const SensorUpdateMsg*>(&message);

     if (castMessage == 0)
     {
        Logger::logDebug("Invalid message: \"" + toString(message.getMessageId()) + "\".\n");
     }
     else
     {
        // Create the JSON object.
        JsonObject& json = jsonBuffer.createObject();

        // Add fields.
        json["command"] = "data";
        json["sensor_reading"] = castMessage->getSensorReading();

        // Serialize to string.
        json.printTo(string);

        serialized = true;
     }
   }
   /*
   // PING_REPLY
   else if (messageId == PingReplyMsg::MESSAGE_ID)
   {
      const PingReplyMsg* castMessage = static_cast<const PingReplyMsg*>(&message);

      if (castMessage == 0)
      {
         Logger::logDebug("Invalid message: \"" + toString(message.getMessageId()) + "\".\n");
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
   else if (messageId == ReadPinReplyMsg::MESSAGE_ID)
   {
      const ReadPinReplyMsg* castMessage = static_cast<const ReadPinReplyMsg*>(&message);

      if (castMessage == 0)
      {
         Logger::logDebug("Invalid message: \"" + toString(message.getMessageId()) + "\".\n");
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
   else if (messageId == WritePinReplyMsg::MESSAGE_ID)
   {
      const WritePinReplyMsg* castMessage = static_cast<const WritePinReplyMsg*>(&message);

      if (castMessage == 0)
      {
         Logger::logDebug("Invalid message: \"" + toString(message.getMessageId()) + "\".\n");
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
   else if (messageId == WifiConfigReplyMsg::MESSAGE_ID)
   {
      const WifiConfigReplyMsg* castMessage = static_cast<const WifiConfigReplyMsg*>(&message);

      if (castMessage == 0)
      {
         Logger::logDebug("Invalid message: \"" + toString(message.getMessageId()) + "\".\n");
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
   // VIBRATION_SENSOR_CONFIG_REPLY
   else if (messageId == VibrationSensorConfigReplyMsg::MESSAGE_ID)
   {
      const VibrationSensorConfigReplyMsg* castMessage = static_cast<const VibrationSensorConfigReplyMsg*>(&message);

      if (castMessage == 0)
      {
         Logger::logDebug("Invalid message: \"" + toString(message.getMessageId()) + "\".\n");
      }
      else
      {
         char buffer[1024];
         sprintf(buffer,
                 VIBRATION_SENSOR_CONFIG_REPLY_HTML.c_str(),
                 castMessage->getSensorId().c_str(),
                 castMessage->getServerIpAddress().c_str(),
                 castMessage->getSensitivity(),
                 castMessage->getResponsiveness());

         string = httpReply(String(buffer));

         serialized = true;
      }
   }
   // MOTOR_CONFIG_REPLY
   else if (messageId == MotorConfigReplyMsg::MESSAGE_ID)
   {
      const MotorConfigReplyMsg* castMessage = static_cast<const MotorConfigReplyMsg*>(&message);

      if (castMessage == 0)
      {
         Logger::logDebug("Invalid message: \"" + toString(message.getMessageId()) + "\".\n");
      }
      else
      {
         char buffer[1024];
         sprintf(buffer,
                 MOTOR_CONFIG_REPLY_HTML.c_str(),
                 castMessage->getSpeed());

         string = httpReply(String(buffer));

         serialized = true;
      }
   }
   */
   else
   {
      Logger::logDebug("Unsupported message: \"" + toString(message.getMessageId()) + "\".\n");
   }

   return (serialized);
}
