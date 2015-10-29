// *****************************************************************************
// *****************************************************************************
// Sensor.h
//
// Author: Jason Tost
// Date:   10.27.2015
//
// *****************************************************************************
// *****************************************************************************

#ifndef SENSOR_H_INCLUDED
#define SENSOR_H_INCLUDED

#include "Esp8266.h"
#include "Message.h"
#include "Pin.h"
#include "Timer.h"

class Sensor
{

public:
   
   // Constructor.
   Sensor(
      // A unique identifer for this sensor.
      const String& sensorId,
      // The GPIO pin that will be used by this sensor.
      const int& pinId);

   // Destructor.
   virtual ~Sensor();

   // Retrieves the sensor id.
   String getSensorId() const;

   // This operation should be called on startup to prepare the sensor for polling/updating.
   virtual void setup() = 0;

   // This operation should be called continuously from within the main control loop.
   virtual void run() = 0;

   // This operation sets the frequency at which this sensor will send updates.
   void setUpdateRate(
      // The rate at which updates shold be sent, in milliseconds.
      const int& updateRate);

   // This operation returns the current reading for this sensor.
   int getCurrentReading() const;

   // This operation handles a message directed to this sensor.
   virtual void handleMessage(
      // The message to handle.
      const Message* message);

protected:

   // This operation retrieves a pointer to the GPIO pin object used by this sensor.
   Pin* getPin() const;

   // A unique identifier for this sensor.
   String sensorId;

   // The pin that will be used to for reading and writing to the sensor.
   int pinId;

   // A timer used in timing the sensor updates.
   Timer updateTimer;

   // The current reading for this sensor.
   int currentReading = 0;
};

// *****************************************************************************
//                               Inline functions

inline String Sensor::getSensorId() const
{
   return (sensorId);
}

inline void Sensor::setUpdateRate(
   const int& updateRate)
{
   updateTimer.start(updateRate);
}

inline int Sensor::getCurrentReading() const
{
   return (currentReading);
}

// This operation retrieves a pointer to the GPIO pin object used by this sensor.
inline Pin* Sensor::getPin() const
{
   return (Esp8266::getInstance()->getPin(pinId));
}

#endif  // SENSOR_H_INCLUDED
