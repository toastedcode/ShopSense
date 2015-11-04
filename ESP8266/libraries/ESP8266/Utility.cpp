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
