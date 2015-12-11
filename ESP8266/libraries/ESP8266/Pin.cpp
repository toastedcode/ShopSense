// *****************************************************************************
// *****************************************************************************
// Pin.cpp
//
// Author: Jason Tost
// Date:   10.27.2015
//
// *****************************************************************************
// *****************************************************************************

#include <Arduino.h>
#include "Pin.h"

Pin::Pin(
   const int& pinId)
{
   this->pinId = pinId;
}

void Pin::setMode(
   const int& mode)
{
   pinMode(pinId, mode);
}

int Pin::read()
{
   return (digitalRead(pinId));
}

void Pin::analogWrite(
   const int& value)
{
   ::analogWrite(pinId, value);
}

void Pin::digitalWrite(
   const int& value)
{
   ::digitalWrite(pinId, value);
}
