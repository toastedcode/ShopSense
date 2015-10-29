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

Esp8266* Esp8266::instance = 0;

Esp8266::Esp8266()
{
   // Nothing to do here.
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
   Serial.println("Connecting to Wifi network " + ssid + "\n");

   WiFi.mode(WIFI_STA);
   WiFi.begin(ssid.c_str(), password.c_str());

   int secondsToConnect = 0;

   // Wait until the connection is made, or until we timeout.
   while ((isConnected() == false) &&
          (secondsToConnect < connectionTimeout))
   {
      delay(1000);
      secondsToConnect++;
      Serial.println(" .");
   }

   if (isConnected())
   {
      Serial.println(" success!\n");
      Serial.println("Connected at " + getIpAddress());
   }
   else
   {
      Serial.println(" failed!\n");
   }

   return (isConnected());
}

bool Esp8266::startAccessPoint(
   const String& ssid,
   const String& password)
{
   // TODO
}

void Esp8266::handleMessage(
   const Message* message)
{

}

void Esp8266::reset()
{
   // TODO
}
