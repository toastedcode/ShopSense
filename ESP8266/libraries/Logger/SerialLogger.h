// *****************************************************************************
// *****************************************************************************
// SerialLogger.h
//
// Author: Jason Tost
// Date:   10.29.2015
//
// *****************************************************************************
// *****************************************************************************

#ifndef SERIALLOGGER_H_INCLUDED
#define SERIALLOGGER_H_INCLUDED

#include "Logger.h"

class SerialLogger : public Logger
{

public:

   SerialLogger();

   virtual ~SerialLogger();

   virtual void log(
      const String& string);

};

#endif  // SERIALLOGGER_H_INCLUDED
