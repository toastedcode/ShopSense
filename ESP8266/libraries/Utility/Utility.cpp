// *****************************************************************************
// *****************************************************************************
// Utility.cpp
//
// Author: Jason Tost
// Date:   11.4.2015
//
// *****************************************************************************

#include "Utility.h"

String Utility::toString(
   const IPAddress& ipAddress)
{
   String string = "";

   for (int octet = 0; octet < 4; octet++)
   {
      string += String(ipAddress[octet]);
      if (octet < 3)
      {
         string += ".";
      }
   }

   return (string);
}


int Utility::findFirstOf(
   const String& string,
   const String& characters,
   const int& position)
{
   int firstPos = -1;

   for (int pos = 0; pos < characters.length(); pos++)
   {
      int foundPos = string.indexOf(characters.charAt(pos), position);

      if (foundPos != -1)
      {
         firstPos = (firstPos == -1) ? foundPos : std::min(firstPos, foundPos);
      }
   }

   return (firstPos);
}

String Utility::tokenize(
   String& string,
   const String& delimiters)
{
   String token = "";

   // Strip off leading delimiters.
   while (findFirstOf(string, delimiters, 0) == 0)
   {
      string = string.substring(1);
   }

   // Now search for first occurance of a delimiter.
   int firstPos = findFirstOf(string, delimiters, 0);

   if (firstPos == -1)
   {
      token = string;
      string = "";
   }
   else
   {
      token = string.substring(0, firstPos);
      string = string.substring(firstPos + 1);
   }

   return (token);
}
