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
   Pin(
      // The GPIO pin id.
      const int& pinId);

   // This operation returns the pin id of the GPIO pin represented by this object.
   int getPinId() const;

   // This operation sets the mode of a GPIO pin.
   void setMode(
      // The new pin mode.
      const int& mode);

   // This operation reads from the sensor pin and returns the current value.   
   int read();
   
   // This operation writes the specified analog value to the PWM pin.
   void analogWrite(
      // The value to write.
      const int& value);

   // This operation writes the specified digital value to the pin.
   void digitalWrite(
      // The value to write.
      const int& value);

private:
   
   // The GPIO pin represented by this class.
   int pinId;
};

// *****************************************************************************
//                               Inline functions

inline int Pin::getPinId() const
{
   return (pinId);
}

#endif  // PIN_H_INCLUDED
