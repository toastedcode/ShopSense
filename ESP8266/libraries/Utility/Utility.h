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

   // This operation returns the next token from the specified string, broken up by any of the specified delimiters.
   static String tokenize(
      // The string to tokenize.
      String& string,
      // A string containing the characters to search for.
      const String& delimiters);
};

#endif  // end UTILITY_H_INCLUDED
