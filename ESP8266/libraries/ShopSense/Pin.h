// *****************************************************************************
// *****************************************************************************
// Pin.h
//
// Author: Jason Tost
// Date:   10.27.2015
//
// *****************************************************************************
// *****************************************************************************

#ifndef PIN_H_INCLUDED
#define PIN_H_INCLUDED

#include "Arduino.h"

// A class representing a GPIO pin on an ESP8266 module.
class Pin
{

public:

   // Constructor.
   Pin(int pinId);

   // This operation reads from the sensor pin and returns the current value.   
   int read();
   
   // This operation writes the specified value to the sensor pin.
   int write(int value);
   
private:
   
   // The GPIO pin represented by this class.
   int pinId;
};

#endif  // PIN_H_INCLUDED