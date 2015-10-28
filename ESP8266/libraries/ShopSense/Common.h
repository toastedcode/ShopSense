// *****************************************************************************
// *****************************************************************************
// Timer.h
//
// Author: Jason Tost
// Date:   9.23.2015
//
// *****************************************************************************
// *****************************************************************************

#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

// Macro for debug printing.
#define DEBUG 1
#define printDebug(str) {if (DEBUG) Serial.print(str);}

// Pin ids for the ESP8266.
// Connect GPIO 1 to sensor.
const int SENSOR_PIN_ID = 2;

// HTTP port
const int HTTP_PORT = 80;

#endif  // COMMON_H_INCLUDED