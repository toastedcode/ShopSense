// *****************************************************************************
// *****************************************************************************
// Utility.h
//
// Author: Jason Tost
// Date:   11.4.2015
//
// *****************************************************************************
// *****************************************************************************

#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED

#include "Arduino.h"
#include "ESP8266WiFi.h"

class Utility
{

public:

   // This operation converts an IPAddress object to a printable string.
   static String toString(
      // The IP address to convert.
      const IPAddress& ipAddress);
};

#endif  // end UTILITY_H_INCLUDED
