// *****************************************************************************
// *****************************************************************************
// Logger.cpp
//
// Author: Jason Tost
// Date:   10.29.2015
//
// *****************************************************************************
// *****************************************************************************

#include "Logger.h"

Logger* Logger::instance = 0;

bool Logger::loggingEnabled = true;

void Logger::setLogger(
   Logger* logger)
{
   if (instance != 0)
   {
      delete instance;
   }

   instance = logger;
}

Logger::Logger()
{

}

Logger::~Logger()
{

}

void Logger::log(
   const String& string)
{
}
