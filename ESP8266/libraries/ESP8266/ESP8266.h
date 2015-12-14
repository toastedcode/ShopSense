// *****************************************************************************
// *****************************************************************************
// EPS8266.h
//
// Author: Jason Tost
// Date:   10.29.2015
//
// *****************************************************************************
// *****************************************************************************

#ifndef ESP8266_H_INCLUDED
#define ESP8266_H_INCLUDED

#include "Arduino.h"
#include "ESP8266WiFi.h"
#include "Pin.h"

class Esp8266
{

public:

   // Get the Singleton instance.
   static Esp8266* getInstance();

   // This operation retrieves the MAC address of the ESP8266.
   String getMacAddress() const;

   // This operation retrieves the current IP address (if connected) of the ESP8266.
   IPAddress getIpAddress() const;

   // This operation attempts to connect to the specified Wifi network using the stored SSID and password.
   // True is returned if the operation was successful; false otherwise.
   // Note: This operation blocks while attempting to make the connection.
   bool connectWifi(
      const int& connectionTimeout = 30);

   // This operation attempts to connect to the specified Wifi network using the specified SSID and password.
   // True is returned if the operation was successful; false otherwise.
   // Note: This operation blocks while attempting to make the connection.
   bool connectWifi(
      // The SSID to use in connecting.
      const String& ssid,
      // The password to use in connecting.
      const String& password,
      // A time (in seconds) to attempt to connect.
      const int& connectionTimeout = 30);

   // This operation return true if the ESP8266 is connected to a Wifi network.
   bool isConnected() const;

   // This operation attempts to create a Wifi access point.
   // True is returned if the operation was successful; false otherwise.
   // Note: This operation blocks while attempting to make the AP.
   bool startAccessPoint(
      // The SSID to use in connecting.
      const String& ssid,
      // The password to use in connecting.
      const String& password);

   // This operation stops any currently started Wifi access point.
   // True is returned if the operation was successful; false otherwise.
   bool stopAccessPoint();

   // Retrieves a pointer to the specified Pin object.
   Pin* getPin(
      const int& pinId) const;

   // Resets the processor.
   void reset();

   // A constant specifying the number of GPIO pins available on the ESP8266.
   static const int MAX_NUM_PINS = 16;

private:

   // Constructor.
   Esp8266();

   // Destructor.
   virtual ~Esp8266();

   // The Singleton instance.
   static Esp8266* instance;

   Pin* pins[MAX_NUM_PINS];

};

// *****************************************************************************
//                               Inline functions

inline Esp8266* Esp8266::getInstance()
{
   if (instance == 0)
   {
      instance = new Esp8266();
   }

   return (instance);
}

inline bool Esp8266::isConnected() const
{
   return (WiFi.status() == WL_CONNECTED);
}

inline Pin* Esp8266::getPin(
   const int& pinId) const
{
   Pin* pin = 0;

   if (pinId < MAX_NUM_PINS)
   {
      pin = pins[pinId - 1];
   }

   return (pin);
}

#endif  // ESP8266_H_INCLUDED
