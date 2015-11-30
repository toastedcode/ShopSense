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

#include "Sensor.h"

class VibrationSensor : public Sensor
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

   // A count of sensor pollings, per update cycle.
   int pollCount;

   // A count of measured vibrations, per update cycle.
   int vibrationCount = 0;

};

#endif  // VIBRATIONSENSOR_H_INCLUDED
