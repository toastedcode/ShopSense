// *****************************************************************************
// *****************************************************************************
// ToastBot.cpp
//
// Author: Jason Tost
// Date:   11.30.2015
//
// *****************************************************************************
// *****************************************************************************

#include "ESP8266.h"
#include "HttpProtocol.h"
#include "Logger.h"
#include "MessageRouter.h"
#include "Messages.h"
#include "SerialAdapter.h"
#include "SerialLogger.h"
#include "ToastBot.h"
#include "Utility.h"

ToastBot* ToastBot::instance;

void ToastBot::begin()
{
   Logger::setLogger(new SerialLogger());
   Logger::setEnabled(true);

   // Register with the message router.
   // Note: Make it the default handler.
   MessageRouter::getInstance()->registerHandler(*(this), true);

   // Setup adapters.
   MessageRouter::getInstance()->registerAdapter(adapter);

   // Connect to a network via the ESP8266 wifi adapter.
   if (Esp8266::getInstance()->connectWifi(15) == false)
   {
      // If the ESP8266 failes to connect with the stored credentials, we'll create an AP to allow for wifi config.
      Esp8266::getInstance()->startAccessPoint("TOASTBOT", "");
   }

   // Start the web server.
   adapter.begin();
}

void ToastBot::run()
{
   MessageRouter::getInstance()->run();
}

bool ToastBot::handleMessage(
   const Message& message)
{
   bool handled = false;

   // PING
   if (message.getMessageId() == PingMsg::MESSAGE_ID)
   {
      Logger::logDebug("Ping\n");
      handled = true;

      String ipAddress = Utility::toString(Esp8266::getInstance()->getIpAddress());
      Message* replyMessage = new PingReplyMsg(ipAddress);
      replyMessage->address(getId(), message.getSource());
      MessageRouter::getInstance()->sendMessage(*replyMessage);
   }
   // SET_LOGGING
   else if (message.getMessageId() == SetLoggingMsg::MESSAGE_ID)
   {
      Logger::logDebug("SetLogging\n");
      handled = true;

      const SetLoggingMsg* castMessage = static_cast<const SetLoggingMsg*>(&message);

      Logger::setEnabled(castMessage->isLoggingEnabled());
   }
   else if (message.getMessageId() == WifiConfigMsg::MESSAGE_ID)
   {
      Logger::logDebug("Wifi Config\n");
      handled = true;

      bool success = false;

      const WifiConfigMsg* castMessage = static_cast<const WifiConfigMsg*>(&message);

      String ssid = castMessage->getSsid();
      String password = castMessage->getPassword();

      Message* replyMessage = new WifiConfigReplyMsg();
      replyMessage->address(getId(), message.getSource());
      MessageRouter::getInstance()->sendMessage(*replyMessage);

      // If we've been provided a new SSID, attempt to connect to that network.
      if (ssid != "")
      {
         Esp8266::getInstance()->connectWifi(ssid, password);

         if (Esp8266::getInstance()->isConnected())
         {
            Esp8266::getInstance()->stopAccessPoint();
         }
      }
   }
   /*
   else if (message.getMessageId() == ResetMsg::MESSAGE_ID)
   {
      Logger::logDebug("Reset\n");

      // TODO
   }
   */
   else if (message.getMessageId() == ReadPinMsg::MESSAGE_ID)
   {
      Logger::logDebug("Read Pin\n");
      handled = true;

      bool success = false;

      const ReadPinMsg* castMessage = static_cast<const ReadPinMsg*>(&message);

      Pin* pin = Esp8266::getInstance()->getPin(castMessage->getPin());

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
   else if (message.getMessageId() == WritePinMsg::MESSAGE_ID)
   {
      Logger::logDebug("Write Pin\n");
      handled = true;

      bool success = false;

      const WritePinMsg* castMessage = static_cast<const WritePinMsg*>(&message);

      Pin* pin = Esp8266::getInstance()->getPin(castMessage->getPin());

      if (pin)
      {
         pin->digitalWrite(castMessage->getValue());
         success = true;
      }

      Message* replyMessage = new WritePinReplyMsg(castMessage->getPin(), castMessage->getValue(), success);
      replyMessage->address(getId(), message.getSource());
      MessageRouter::getInstance()->sendMessage(*replyMessage);
   }
   /*
   else if (message.getMessageId() == SetPinModeMsg::MESSAGE_ID)
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
