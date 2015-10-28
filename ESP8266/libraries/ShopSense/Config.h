// *****************************************************************************
// *****************************************************************************
// Config.h
//
// Author: Jason Tost
// Date:   10.27.2015
//
// *****************************************************************************
// *****************************************************************************

#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

// A structure containing sensor configuration data.
struct Config
{
   // The SSID of the Wifi network to which this sensor should connect.
   const char* ssid = "";
   
   // The password that this sensor should use in connecting to the Wifi network.
   const char* password = "";
   
   // The unique sensor id to be used when posting readings to the server.
   const char* sensorId = "";
   
   // The rate (in milliseconds) at which the sensor pin will be polled.
   int pollRate = 0;

   // The rate (in milliseconds) at which the sensor reading will be calcuated and sent to the server.
   int updateRate = 0;

   // A flag indicating if the sensor should only report changed sensor values.
   bool reportOnChanged = false;
   
   // The address of the sensor server.
   const char* serverAddress = "";
};

#endif  // CONFIG_H_INCLUDED
