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
#include "Message.h"
#include "Pin.h"

class Esp8266
{

public:

   // Constructor.
   Esp8266();

   // Destructor.
   virtual ~Esp8266();

   // Gets an instance to the Singleton.
   static Esp8266* getInstance();

   // This operation retrieves the MAC address of the ESP8266.
   String getMacAddress() const;

   // This operation retrieves the current IP address (if connected) of the ESP8266.
   IPAddress getIpAddress() const;

   // This operation attempts to connect to the specified Wifi network.
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

   // Retrieves a pointer to the specified Pin object.
   Pin* getPin(
      const int& pinId) const;

   // This operation handles a message directed to the ESP8266 itself.
   void handleMessage(
      // The message to handle.
      const Message* message);

   // Resets the processor.
   void reset();

   // A constant specifying the number of GPIO pins available on the ESP8266.
   static const int MAX_NUM_PINS = 12;

private:

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
   return (pins[pinId - 1]);
}

#endif  // ESP8266_H_INCLUDED
