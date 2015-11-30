// *****************************************************************************
// *****************************************************************************
// ESP8266.cpp
//
// Author: Jason Tost
// Date:   10.29.2015
//
// *****************************************************************************
// *****************************************************************************

#include "ESP8266.h"
#include "Logger.h"
#include "MessageRouter.h"
#include "PingMsg.h"
#include "PingReplyMsg.h"
#include "ReadPinMsg.h"
#include "ReadPinReplyMsg.h"
#include "Utility.h"
#include "WifiConfigMsg.h"
#include "WifiConfigReplyMsg.h"
#include "WritePinMsg.h"
#include "WritePinReplyMsg.h"

Esp8266* Esp8266::instance = 0;

Esp8266::Esp8266() : MessageHandler(ESP8266_ID)
{
   // Create pins.
   for (int pinId = 1; pinId <= MAX_NUM_PINS; pinId++)
   {
      pins[pinId - 1] = new Pin(pinId);
   }
}

Esp8266::~Esp8266()
{
   // Delete pins.
   for (int pinId = 1; pinId <= MAX_NUM_PINS; pinId++)
   {
      if (pins[pinId - 1])
      {
         delete pins[pinId - 1];
      }
   }
}

void Esp8266::setup()
{
   // Register with the Message Router.
   MessageRouter::getInstance()->registerHandler(*this, true);
}

String Esp8266::getMacAddress() const
{
   unsigned char macAddress[6];
   WiFi.macAddress(macAddress);

   //return (String(macAddress));
   return ("");
}

IPAddress Esp8266::getIpAddress() const
{
   return (WiFi.localIP());
}

bool Esp8266::connectWifi(
   const String& ssid,
   const String& password,
   const int& connectionTimeout)
{
   Logger::logDebug("Connecting to Wifi network " + ssid);

   WiFi.mode(WIFI_STA);
   WiFi.begin(ssid.c_str(), password.c_str());

   int secondsToConnect = 0;

   // Wait until the connection is made, or until we timeout.
   while ((isConnected() == false) &&
          (secondsToConnect < connectionTimeout))
   {
      delay(1000);
      secondsToConnect++;
      Logger::logDebug(" .");
   }

   if (isConnected())
   {
      Logger::logDebug(" success!\n");
      Logger::logDebug("Connected at " + Utility::toString(getIpAddress()) + "\n");
   }
   else
   {
      Logger::logDebug(" failed!\n");
   }

   return (isConnected());
}

bool Esp8266::startAccessPoint(
   const String& ssid,
   const String& password)
{
   WiFi.mode(WIFI_AP);
   WiFi.softAP(ssid.c_str(), password.c_str());
}

bool Esp8266::handleMessage(
   const Message& message)
{
   bool handled = false;

   if (message.getMessageId() == PingMsg::getMessageId())
   {
      Logger::logDebug("Ping\n");

      String ipAddress = Utility::toString(getIpAddress());
      Message* replyMessage = new PingReplyMsg(ipAddress);
      replyMessage->address(getId(), message.getSource());
      MessageRouter::getInstance()->sendMessage(*replyMessage);
   }
   else if (message.getMessageId() == WifiConfigMsg::getMessageId())
   {
      Logger::logDebug("Wifi Config\n");

      bool success = false;

      const WifiConfigMsg* castMessage = static_cast<const WifiConfigMsg*>(&message);

      String ssid = castMessage->getSsid();
      String password = castMessage->getPassword();

      Message* replyMessage = new WifiConfigReplyMsg();
      replyMessage->address(getId(), message.getSource());
      MessageRouter::getInstance()->sendMessage(*replyMessage);

      connectWifi(ssid, password);
   }
   /*
   else if (message.getMessageId() == ResetMsg::getMessageId())
   {
      Logger::logDebug("Reset\n");

      // TODO
   }
   */
   else if (message.getMessageId() == ReadPinMsg::getMessageId())
   {
      Logger::logDebug("Read Pin\n");

      bool success = false;

      const ReadPinMsg* castMessage = static_cast<const ReadPinMsg*>(&message);

      Pin* pin = getPin(castMessage->getPin());

      int value = 0;
      if (pin)
      {
         value = pin->read();
         success = true;
      }

      Message* replyMessage = new ReadPinReplyMsg(castMessage->getPin(), value, success);
      replyMessage->address(getId(), message.getSource());
      MessageRouter::getInstance()->sendMessage(*replyMessage);
   }
   else if (message.getMessageId() == WritePinMsg::getMessageId())
   {
      Logger::logDebug("Write Pin\n");

      bool success = false;

      const WritePinMsg* castMessage = static_cast<const WritePinMsg*>(&message);

      Pin* pin = getPin(castMessage->getPin());

      if (pin)
      {
         pin->write(castMessage->getValue());
         success = true;
      }

      Message* replyMessage = new WritePinReplyMsg(castMessage->getPin(), castMessage->getValue(), success);
      replyMessage->address(getId(), message.getSource());
      MessageRouter::getInstance()->sendMessage(*replyMessage);
   }
   /*
   else if (message.getMessageId() == SetPinModeMsg::getMessageId())
   {
      Logger::logDebug("Set Pin Mode\n");

      bool success = false;

      const SetPinModeMsg* castMessage = static_cast<const SetPinModeMsg*>(&message);

      Pin* pin = getPin(castMessage.getPin());

      if (pin)
      {
         pin->setMode(castMessage->getPinMode());
         success = true;
      }

      Message* replyMessage = new SetPinModeReplyMsg(success, castMessage->getPinMode());
      replyMessage->address(getId(), message->getSource());
      MessageRouter::getInstance()->sendMessage(*replyMessage);
   }
   */

   return (handled);
}

void Esp8266::reset()
{
   // TODO
}
