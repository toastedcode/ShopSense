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

class Timer
{

public:

   // This operation starts the timer.
   void start(
      // The delay (in milliseconds) of the timer.
      int delay);

   // This operation return true if the timer has expired.
   bool isExpired();
   
private:

   // The delay (in milliseconds) associated with this timer.
   int delay;

   // The time at which this timer was started.
   int startTime;
};

#endif
