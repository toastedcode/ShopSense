// *****************************************************************************
// *****************************************************************************
// Flash.cpp
//
// Author: Jason Tost
// Date:   12.22.2015
//
// *****************************************************************************
// *****************************************************************************

#include <Arduino.h>
#include "Flash.h"

// **************************************************************************
//                                  Public
// **************************************************************************

void Flash::write(
   const int& location,
   const String& string)
{
   // The trick here is that flash memory must be read and written on 32-bit boundaries.
   // So if the location is not aligned, we must read from flash memory into a buffer, write to that buffer,
   // and then write back to flash.


}

void Flash::read(
   const int& location,
   String& string)
{

}

void Flash::readLine(
   const int& location,
   String& string)
{

}

// **************************************************************************
//                                  Private
// **************************************************************************

int Flash::getSector(
   const int& location)
{
   return (0);
}
