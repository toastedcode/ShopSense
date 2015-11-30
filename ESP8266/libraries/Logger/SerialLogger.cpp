// *****************************************************************************
// *****************************************************************************
// SerialLogger.cpp
//
// Author: Jason Tost
// Date:   10.29.2015
//
// *****************************************************************************
// *****************************************************************************

#include "SerialLogger.h"

SerialLogger::SerialLogger() : Logger()
{
}

SerialLogger::~SerialLogger()
{

}

void SerialLogger::log(
   const String& string)
{
   Serial.print(string);
}
