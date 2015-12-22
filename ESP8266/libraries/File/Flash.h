// *****************************************************************************
// *****************************************************************************
// Flash.h
//
// Author: Jason Tost
// Date:   12.22.2015
//
// *****************************************************************************
// *****************************************************************************

#ifndef FLASH_H_INCLUDED
#define FLASH_H_INCLUDED

#include "Arduino.h"

class Flash
{

public:

   static void write(
      const int& location,
      const String& string);

   static void read(
      const int& location,
      String& string);

   static void readLine(
      const int& location,
      String& string);

private:

   static int getSector(
      const int& location);

};

#endif  // FLASH_H_INCLUDED
