// *****************************************************************************
// *****************************************************************************
// WebTime.cpp
//
// Author: Jason Tost
// Date:   2.11.2016
//
// *****************************************************************************
// *****************************************************************************

#include "WebTime.h"

const String WebTime::DEFAULT_TIME_SERVER = "www.google.com";

WiFiClient WebTime::client;

// Default HTTP port.
static const int HTTP_PORT = 80;

// A HTTP 1.1 request which is missing "Host: header"
// Note: Compliant servers are required to answer with an error that includes
// a "Date: header".
static const String HTTP_REQUEST = "GET / HTTP/1.1 \r\n\r\n";

// Inspired by http://playground.arduino.cc//Code/Webclient
long WebTime::getTime()
{
   unsigned long time = 0;

   // Just choose any reasonably busy web server, the load is really low
   if (client.connect(DEFAULT_TIME_SERVER.c_str(), HTTP_PORT))
   {
      // Make an HTTP 1.1 request which is missing a Host: header
      // compliant servers are required to answer with an error that includes
      // a Date: header.
      client.print(HTTP_REQUEST.c_str());

      char buf[5];                      // temporary buffer for characters
      client.setTimeout(5000);
      if ((client.find((char *)"\r\nDate: ")) && // look for Date: header
          (client.readBytes(buf, 5) == 5))       // discard
      {
         unsigned day = client.parseInt();  // day
         client.readBytes(buf, 1);          // discard
         client.readBytes(buf, 3);          // month
         String month = String(buf);
         int year = client.parseInt();      // year
         byte hour = client.parseInt();     // hour
         byte minute = client.parseInt();   // minute
         byte second = client.parseInt();   // second

         time = getUnixTime(year, month, day, hour, minute, second);
      }
   }

   client.flush();
   client.stop();

   return (time);
}

// Inspired by http://playground.arduino.cc//Code/Webclient
unsigned long WebTime::getUnixTime(
   int year,
   String month,
   unsigned day,
   byte hour,
   byte minute,
   byte second)
{
   unsigned long time = 0;

   int daysInPrevMonths = 0;
   switch (month.charAt(0))
   {
      case 'F': daysInPrevMonths =  31; break; // Feb
      case 'S': daysInPrevMonths = 243; break; // Sep
      case 'O': daysInPrevMonths = 273; break; // Oct
      case 'N': daysInPrevMonths = 304; break; // Nov
      case 'D': daysInPrevMonths = 334; break; // Dec
      default:
      {
         if ((month.charAt(0) == 'J') &&
             (month.charAt(1) == 'a'))
         {
            daysInPrevMonths = 0;           // Jan
         }
         else if ((month.charAt(0) == 'A') &&
                  (month.charAt(1) == 'p'))
         {
            daysInPrevMonths = 90;          // Apr
         }
         else
         {
            switch (month.charAt(2))
            {
               case 'r': daysInPrevMonths =  59; break; // Mar
               case 'y': daysInPrevMonths = 120; break; // May
               case 'n': daysInPrevMonths = 151; break; // Jun
               case 'l': daysInPrevMonths = 181; break; // Jul
               default: // add a default label here to avoid compiler warning
               case 'g': daysInPrevMonths = 212; break; // Aug
            }
         }
      }
   }

   // This code will not work after February 2100
   // because it does not account for 2100 not being a leap year and because
   // we use the day variable as accumulator, which would overflow in 2149
   day += (year - 1970) * 365;      // days from 1970 to the whole past year
   day += (year - 1969) >> 2;       // plus one day per leap year
   day += daysInPrevMonths;         // plus days for previous months this year
   if ((daysInPrevMonths >= 59) &&  // if we are past February
       ((year & 3) == 0))           // and this is a leap year
   {
      day += 1;  // add one day
   }

   // Remove today, add hours, minutes and seconds this month
   time = (((day-1ul) * 24 + hour) * 60 + minute) * 60 + second;

   return (time);
}
