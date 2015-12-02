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

   // This operation searches a string for the first character that matches any of the specified characters.
   static int findFirstOf(
      // The string to search.
      const String& string,
      // A string containing the characters to search for.
      const String& characters,
      // The position in the string to start the search.
      const int& position = 0);
};

#endif  // end UTILITY_H_INCLUDED
