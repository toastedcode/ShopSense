// *****************************************************************************
// *****************************************************************************
// ButtonSensor.h
//
// Author: Jason Tost
// Date:   10.27.2015
//
// *****************************************************************************
// *****************************************************************************

#ifndef BUTTONSENSOR_H_INCLUDED
#define BUTTONSENSOR_H_INCLUDED

#include "Sensor.h"

class ButtonSensor : public Sensor
{

public:
   
   // Constructor.
   ButtonSensor(
      // A unique identifer for this sensor.
      const String& sensorId,
      // The GPIO pin that will be used by this sensor.
      const int& pinId);

   // Destructor.
   virtual ~ButtonSensor();

   // This operation should be called on startup to prepare the sensor for polling/updating.
   virtual void setup();

   // This operation should be called continuously from within the main control loop.
   virtual void run();

   // This operation handles a message directed to this sensor.
   virtual void handleMessage(
      // The message to handle.
      const Message* message);
   
};

#endif  // BUTTONSENSOR_H_INCLUDED
