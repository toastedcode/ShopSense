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
#include "Utility.h"

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
   // Nothing to do here.
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
   // TODO
}

bool Esp8266::handleMessage(
   const Message& message)
{
   // TODO
}

void Esp8266::reset()
{
   // TODO
}
