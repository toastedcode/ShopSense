// *****************************************************************************
// *****************************************************************************
// Timer.h
//
// Author: Jason Tost
// Date:   9.23.2015
//
// *****************************************************************************
// *****************************************************************************

#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include "Arduino.h"

class Timer
{

public:

   // This operation starts the timer.
   void start(
      // The delay (in milliseconds) of the timer.
      const int& delay);

   // This operation restarts the timer with the current delay.
   void restart();

   // This operation stops the timer.
   void stop();

   // This operation return true if the timer is running.
   bool isRunning() const;

   // This operation return true if the timer has expired.
   bool isExpired() const;
   
private:

   // The delay (in milliseconds) associated with this timer.
   int delay;

   // The time at which this timer was started.
   // Will be set to zero if the timer is not currently running.
   int startTime;
};

// *****************************************************************************
//                               Inline functions

inline void Timer::stop()
{
   startTime = 0;
}

inline bool Timer::isRunning() const
{
   return (startTime == 0);
}

inline bool Timer::isExpired() const
{
   return ((isRunning() == true) &&
           ((millis() - startTime) > delay));
}

#endif
