// *****************************************************************************
// *****************************************************************************
// WebTime.h
//
// Author: Jason Tost
// Date:   2.11.2016
//
// *****************************************************************************
// *****************************************************************************

#ifndef WEBTIME_H_INCLUDED
#define WEBTIME_H_INCLUDED

#include "Arduino.h"
#include "ESP8266WiFi.h"

class WebTime
{

public:

   static long getTime();

   static const String DEFAULT_TIME_SERVER;

private:

   static unsigned long getUnixTime(
      int year,
      String month,
      unsigned day,
      byte hour,
      byte minute,
      byte second);

   // A reusable client object for sending HTTP messages.
   static WiFiClient client;
};

#endif  // WEBTIME_H_INCLUDED
