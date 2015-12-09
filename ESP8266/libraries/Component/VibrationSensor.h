// *****************************************************************************
// *****************************************************************************
// VibrationSensor.h
//
// Author: Jason Tost
// Date:   10.27.2015
//
// *****************************************************************************
// *****************************************************************************

#ifndef VIBRATIONSENSOR_H_INCLUDED
#define VIBRATIONSENSOR_H_INCLUDED

#include "Component.h"
#include "Timer.h"

class VibrationSensor : public Component
{

public:
   
   // Constructor.
   VibrationSensor(
      // A unique identifer for this sensor.
      const String& id,
      // The GPIO pin that will be used by this sensor.
      const int& pinId);

   // Destructor.
   virtual ~VibrationSensor();

   // This operation should be called on startup to prepare the sensor for polling/updating.
   virtual void setup();

   // This operation should be called continuously from within the main control loop.
   virtual void run();

   // This operation handles a message directed to this sensor.
   virtual bool handleMessage(
      // The message to handle.
      const Message& message);

private:

   const int DEFAULT_SENSITIVITY = 100;

   const int DEFAULT_RESPONSIVENESS = 5;

   const int INTERVAL_TIME = 500;  // milliseconds

   static const int NUM_INTERVALS = 10;

   static const int VIBRATING = 1;

   static const int NOT_VIBRATING = 0;

   // The GPIO pin attached to the vibration sensor.
   int pinId;

   // A multiplier used in adjusting how sensitive the sensor is to vibrations.
   int sensitivity;

   // A multiplier used in adjusting quickly the sensor reacts to changes in vibration.
   int responsiveness;

   // A timer used in periodically tallying the number of recorded vibrations.
   Timer intervalTimer;

   // A circular queue, recording the vibrating state over a number of time intervals.
   int queue[NUM_INTERVALS];

   // The current position in the circular queue.
   int queuePosition = 0;

   // The current overall state of the sensor.
   int state = NOT_VIBRATING;

   // The current reading of the GPIO pin.
   int reading = LOW;

   // A running count of the number of vibrations detected for the current interval.
   int vibrationCount = 0;
};

#endif  // VIBRATIONSENSOR_H_INCLUDED
