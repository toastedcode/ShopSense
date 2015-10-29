// *****************************************************************************
// *****************************************************************************
// Timer.h
//
// Author: Jason Tost
// Date:   9.23.2015
//
// *****************************************************************************
// *****************************************************************************

#include "Timer.h"

void Timer::start(
   const int& delay)
{
   this->delay = delay;
   startTime = millis();
}

void Timer::restart()
{
   startTime = millis();
}