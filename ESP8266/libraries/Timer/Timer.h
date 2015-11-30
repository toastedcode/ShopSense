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

   // Constructor.
   Timer();

   // Constructor.
   Timer(
      // The delay (milliseconds).
      const int& delay);

   // Destructor.
   ~Timer();

   // This operation sets the delay for the timer.
   void setDelay(
      // The delay (milliseconds).
      int delay);

   // This operation starts the timer.
   void start();

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

inline void Timer::setDelay(
   int delay)
{
   this->delay = delay;
}

inline void Timer::start()
{
   startTime = millis();
}

inline void Timer::stop()
{
   startTime = 0;
}

inline bool Timer::isRunning() const
{
   return (startTime != 0);
}

inline bool Timer::isExpired() const
{
   return ((isRunning() == true) &&
           ((millis() - startTime) > delay));
}

#endif
