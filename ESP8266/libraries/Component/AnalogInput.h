// *****************************************************************************
// *****************************************************************************
// AnalogInput.h
//
// Author: Jason Tost
// Date:   11.23.2015
//
// *****************************************************************************
// *****************************************************************************

#ifndef ANALOG_INPUT_H_INCLUDED
#define ANALOG_INPUT_H_INCLUDED

#include "Sensor.h"

class AnalogInput : public MessageHandler
{

public:

   // Constructor.
   AnalogInput(
      // A unique identifer for this component.
      const String& id,
      // The GPIO pin that will be used by this component.
      const Pin* pin);

   // Destructor.
   virtual ~AnalogInput();

   // This operation should be called on startup to prepare the sensor for polling/updating.
   virtual void setup();

   // This operation should be called continuously from within the main control loop.
   virtual void run();

   // This operation handles a message directed to this sensor.
   virtual bool handleMessage(
      // The message to handle.
      const Message& message);

protected:

   // A pointer to the pin object used by the sensor.
   Pin* pin;

};

#endif  // ANALOG_INPUT_H_INCLUDED
