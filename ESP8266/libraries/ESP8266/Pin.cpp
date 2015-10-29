// *****************************************************************************
// *****************************************************************************
// Pin.cpp
//
// Author: Jason Tost
// Date:   10.27.2015
//
// *****************************************************************************
// *****************************************************************************

#include "Pin.h"

Pin::Pin(
   const int& pinId)
{
   this->pinId = pinId;
}
  
int Pin::read()
{
   pinMode(pinId, INPUT);
   return (digitalRead(pinId));
}
   
int Pin::write(
   const int& value)
{
   pinMode(pinId, OUTPUT);
   digitalWrite(pinId, value);
}
