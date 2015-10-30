// *****************************************************************************
// *****************************************************************************
// Logger.h
//
// Author: Jason Tost
// Date:   10.29.2015
//
// *****************************************************************************
// *****************************************************************************

#ifndef LOGGER_H_INCLUDED
#define LOGGER_H_INCLUDED

#include "Arduino.h"

class Logger
{

public:

   Logger();

   virtual ~Logger();

   static void setLogger(
      Logger* logger);

   static void logDebug(
      const String& string);

   virtual void log(
      const String& string);

protected:

   static Logger* getInstance();

private:

   static Logger* instance;

};

// *****************************************************************************
//                               Inline functions

inline void Logger::logDebug(
   const String& string)
{
   getInstance()->log(string);
}

inline Logger* Logger::getInstance()
{
   return (instance);
}

#endif  // LOGGER_H_INCLUDED
