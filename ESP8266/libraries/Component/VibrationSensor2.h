// *****************************************************************************
// *****************************************************************************
// VibrationSensor2.h
//
// Author: Jason Tost
// Date:   10.27.2015
//
// *****************************************************************************
// *****************************************************************************

#ifndef VibrationSensor2_H_INCLUDED
#define VibrationSensor2_H_INCLUDED

#include <Arduino.h>
#include "Component.h"
#include "Timer.h"

class VibrationSensor2 : public Component
{

public:
   
   // Constructor.
   VibrationSensor2(
      // A unique identifer for this sensor.
      const String& id,
      // The GPIO pin that will be used by this sensor.
      const int& pinId);

   // Destructor.
   virtual ~VibrationSensor2();

   // This operation should be called on startup to prepare the sensor for polling/updating.
   virtual void setup();

   // This operation should be called continuously from within the main control loop.
   virtual void run();

   // This operation handles a message directed to this sensor.
   virtual bool handleMessage(
      // The message to handle.
      const Message& message);

   // This operation sets the server id that will be used in making updates to an IoT server.
   void setServerId(
      // The server id.
      const String& serverId);

private:

   // Returns the number of intervals we're using to detect vibration.
   // Note: This value is calculated using the configured responsiveness.
   int getIntervalCount() const;

   // Returns the number of detected vibrations necessary for changing the overall vibration state.
   // Note: This value is calculated using the configured sensitivity.
   int getVibrationThreshold() const;

   const int DEFAULT_SENSITIVITY = 1;  // %

   const int DEFAULT_RESPONSIVENESS = 25;  // %

   const int INTERVAL_TIME = 500;  // milliseconds

   const int UPDATE_TIME = 10000;  // milliseconds

   static const int NUM_INTERVALS = 20;  // 10 seconds of historical data

   static const int VIBRATING = 1;

   static const int NOT_VIBRATING = 0;

   // The adapter id used in sending updates to a IOT server.
   String serverId;

   // The GPIO pin attached to the vibration sensor.
   int pinId;

   // A % multiplier used in adjusting how sensitive the sensor is to vibrations.
   int sensitivity;

   // A % multiplier used in adjusting quickly the sensor reacts to changes in vibration.
   int responsiveness;

   // A timer used in periodically tallying the number of recorded vibrations.
   Timer intervalTimer;

   // A timer used in periodically updating the server with the current sensor state.
   Timer updateTimer;

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

   // A time (in milliseconds) indicating the time that the sensor last changed its state.
   // Used in computing how long the sensor has been in the VIBRATING/NOT_VIBRATING state.
   int stateChangeTime = 0;
};

inline void VibrationSensor2::setServerId(
   const String& serverId)
{
   this->serverId = serverId;
}

inline int VibrationSensor2::getIntervalCount() const
{
   const int MIN_INTERVAL_COUNT = 1;
   const int MAX_INTERVAL_COUNT = NUM_INTERVALS;

   return (constrain(((MAX_INTERVAL_COUNT * responsiveness) / 100), MIN_INTERVAL_COUNT, MAX_INTERVAL_COUNT));
}

inline int VibrationSensor2::getVibrationThreshold() const
{
   const int MIN_VIBRATION_THRESHOLD = 1;
   const int MAX_VIBRATION_THRESHOLD = 100;

   return (constrain(((MAX_VIBRATION_THRESHOLD * sensitivity) / 100), MIN_VIBRATION_THRESHOLD, MAX_VIBRATION_THRESHOLD));
}

#endif  // VibrationSensor2_H_INCLUDED
