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
#include "Messages.h"
#include "Utility.h"

static const bool REQUIRED = true;
static const bool OPTIONAL = false;

static const String PING_REPLY_HTML = "<html><body><div>Ping reply from %s</div></body></html>";
static const String READ_PIN_REPLY_HTML = "<html><body><div>(%s) Read pin %d, value = %d</div></body></html>";
static const String WRITE_PIN_REPLY_HTML = "<html><body><div>(%s) Write pin %d, value = %d</div></body></html>";
static const String WIFI_CONFIG_REPLY_HTML = "<html><b>Wifi Setup</b></p><form method=\"get\" action=\"#\"><input type=\"hidden\" name=\"command\" value=\"wifi_config\"/><table><tr><td>SSID:</td><td><input type=\"text\" name=\"ssid\"/></td></tr><tr><td>Password:</td><td><input type=\"password\" name=\"password\"/></td></tr><tr><td><input type=\"submit\" value=\"Submit\"></td></tr></table></form></html>";
static const String VIBRATION_SENSOR_CONFIG_REPLY_HTML = "<html><b>Vibration Sensor Config</b></p><form method=\"get\" action=\"#\"><table><tr><td>Sensor id:</td><td><input type=\"text\" name=\"sensor_id\" value=\"%s\"/></td></tr><tr><td>Server IP:</td><td><input type=\"text\" name=\"server_ip\" value=\"%s\"/></td></tr><tr><td>Sensitivity:</td><td><input type=\"range\" name=\"sensitivity\" min=\"1\" max=\"100\" value=\"%d\"></td></tr><tr><td>Responsiveness:</td><td><input type=\"range\" name=\"responsiveness\" min=\"1\" max=\"100\" value=\"%d\"><td></tr><tr><td><input type=\"submit\" value=\"Submit\"></td></tr></table></form></html>";
//static const String MOTOR_CONFIG_REPLY_HTML = "<html><b>Motor Config</b></p><form method=\"get\" action=\"#\"><table><tr><td>Speed:</td><td><input type=\"range\" name=\"speed\" min=\"-1023\" max=\"1023\" value=\"%d\"/></td></tr><tr><td><input type=\"submit\" value=\"Submit\"/></td></tr></table></form></html>";
static const String MOTOR_CONFIG_REPLY_HTML = "<html><b>Motor Config</b></p><form method=\"get\" action=\"#\">   <table>      <tr>         <td>Speed:</td>         <td><input id=\"speedInput\" type=\"range\" name=\"speed\" min=\"-1023\" max=\"1023\" value=\"%d\" oninput=\"onChange(this.value)\" onmouseup=\"onMouseUp()\"/></td>      </tr>      <tr>         <td><input type=\"submit\" value=\"Submit\"/></td>      </tr>   </table></form><script>function onMouseUp(){   document.getElementById(\"speedInput\").value = 0;     onChange(0);}function onChange(value){    var xhttp = new XMLHttpRequest();  xhttp.open(\"GET\", \"/motor1/motor_config?speed=\" + value, true);     xhttp.send();}</script></html>";

bool HttpProtocol::parse(
   const String& string,
   Message*& message)
{
   bool parsed = false;
   message = 0;

   Logger::logDebug("Parsing: " + string + "\n");

   String component = "";
   String command = "";
   String parameters = "";

   parsed = tokenizeMessage(string, component, command, parameters);

   if (parsed)
   {
      Logger::logDebug("Component: " + component + "\n");
      Logger::logDebug("Command: " + command + "\n");
      Logger::logDebug("Parameters: " + parameters + "\n");

      // PING_MSG
      // Format: ping
      if (command == "ping")
      {
         message = new PingMsg();
         parsed = true;
      }
      // SET_LOGGING_MSG
      // Format: ping
      else if (command == "logging")
      {
         String loggingEnabled = "";

         if (getParameter(string, "enabled", REQUIRED, loggingEnabled))
         {
            message = new SetLoggingMsg((loggingEnabled == "true"));
            parsed = true;
         }
         else
         {
            Logger::logDebug("Bad message format: \"" + string + "\".\n");
         }
      }
      // READ_PIN_MSG
      // Format: read?pin=<pin id>
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
      // Format: write?pin=<pin id>&value=<value>
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
      // WIFI_CONFIG
      // Format: wifi_config?ssid=<ssid>&password=<password>
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
      // Format: vibration_sensor_config?server_ip=&sensitivity=&responsiveness=&update_rate=&is_enabled=
      else if (command == "vibration_sensor_config")
      {
         String sensorId = "";
         String serverIpAddress = "";
         String sensitivity =  "0";
         String responsiveness = "0";
         String updateRate = "";
         String isEnabled = "";

         if (getParameter(string, "sensor_id", OPTIONAL, sensorId) &&
             getParameter(string, "server_ip", OPTIONAL, serverIpAddress) &&
             getParameter(string, "sensitivity", OPTIONAL, sensitivity) &&
             getParameter(string, "responsiveness", OPTIONAL, responsiveness) &&
             getParameter(string, "is_enabled", OPTIONAL, isEnabled))
         {
            message = new VibrationSensorConfigMsg(sensorId,
                                                   serverIpAddress,
                                                   sensitivity.toInt(),
                                                   responsiveness.toInt(),
                                                   ((isEnabled == "true") ? true : false));
            parsed = true;
         }
         else
         {
            Logger::logDebug("Bad message format: \"" + string + "\".\n");
         }
      }
      // MOTOR_CONFIG
      // Format: motor_config?speed=
      else if (command == "motor_config")
      {
         String speed = "";

         if (getParameter(string, "speed", REQUIRED, speed))
         {
            message = new MotorConfigMsg(speed.toInt());
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
         message->address("", component);
      }
      else
      {
         Logger::logDebug("Unsupported message: \"" + command + "\".\n");
      }
   }

   return (parsed);
}

bool HttpProtocol::serialize(
   const Message& message,
   String& string)
{
   bool serialized = false;

   MessageId messageId = message.getMessageId();

   // SENSOR_UPDATE
   // Format: command=data&sensor_id=<sensor id>&sensor_reading=<sensor reading>
   if (messageId == SensorUpdateMsg::MESSAGE_ID)
   {
     const SensorUpdateMsg* castMessage = static_cast<const SensorUpdateMsg*>(&message);

     if (castMessage == 0)
     {
        Logger::logDebug("Invalid message: \"" + toString(message.getMessageId()) + "\".\n");
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
   else
   {
      Logger::logDebug("Unsupported message: \"" + toString(message.getMessageId()) + "\".\n");
   }

   return (serialized);
}

bool HttpProtocol::tokenizeMessage(
   const String& string,
   String& component,
   String& command,
   String& parameters)
{
   const int MAX_NUM_TOKENS = 3;
   const String FORWARD_SLASH = "/";
   const String SEPERATORS = "/? ";
   const String PARAM_START = "?";
   const String GET = "GET";
   const String HTTP = "HTTP";

   bool success = true;

   // Format:
   //
   // GET /<component>/<command>?<params> HTTP/1.1
   // GET /<component>/<command> HTTP/1.1
   // GET /<command>?<params> HTTP/1.1
   // GET /<command> HTTP/1.1

   String remainingString = string;

   // Strip off GET.
   int foundPos = remainingString.indexOf(GET);
   if (foundPos != -1)
   {
      int startPos = remainingString.indexOf(FORWARD_SLASH, foundPos);
      remainingString = remainingString.substring(startPos);
   }

   // Strip off HTTP.
   foundPos = remainingString.indexOf(HTTP);
   if (foundPos != -1)
   {
      int startPos = 0;
      int endPos = foundPos;
      remainingString = remainingString.substring(startPos, endPos);
   }

   String tokens[MAX_NUM_TOKENS] = {"", "", ""};

   int i = 0;
   tokens[i] = Utility::tokenize(remainingString, SEPERATORS);

   while (remainingString.length() > 0)
   {
      String token =  Utility::tokenize(remainingString, SEPERATORS);

      i++;
      if (i < MAX_NUM_TOKENS)
      {
         tokens[i] = token;
      }
   }

   int tokenCount = (i + 1);

   bool hasParams = (Utility::findFirstOf(string, PARAM_START) != -1);

   switch (tokenCount)
   {
      case 1:
      {
         // GET /<command> HTTP/1.1
         component = "";
         command = tokens[0];
         parameters = "";
         break;
      }

      case 2:
      {
         // GET /<command>?<params> HTTP/1.1
         if (hasParams)
         {
            component = "";
            command = tokens[0];
            parameters = tokens[1];
         }
         // GET /<component>/<command> HTTP/1.1
         else
         {
            component = tokens[0];
            command = tokens[1];
         }
         break;
      }

      case 3:
      {
         // GET /<component>/<command>?<params> HTTP/1.1
         component = tokens[0];
         command = tokens[1];
         parameters = tokens[2];
         break;
      }

      default:
      {
         Logger::logDebug("Too many tokens in message.\n");
         success = false;
         break;
      }
   }

   component.trim();
   command.trim();
   parameters.trim();

   return (success);
}

bool HttpProtocol::getParameter(
   const String& string,
   const String& parameterName,
   const bool& isRequired,
   String& parameter)
{
   const String PARAM_SEPERATORS = "& ";
   const String SPACE = " ";

   bool success = !isRequired;

   // Format:
   // GET /<component>/<command>/?<params>
   // GET /<command>/?<params>

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
