// *****************************************************************************
// *****************************************************************************
// Motor.h
//
// Author: Jason Tost
// Date:   12.10.2015
//
// *****************************************************************************
// *****************************************************************************

#ifndef MOTOR_H_INCLUDED
#define MOTOR_H_INCLUDED

#include "Component.h"
#include "Timer.h"

class Motor : public Component
{

public:
   
   // Constructor.
   Motor(
      // A unique identifer for this sensor.
      const String& id,
      // The GPIO pin that will be used to set the motor direction.
      const int& directionPinId,
      // The GPIO pin that will be used to set the motor speed.
      const int& speedPinId);

   // Destructor.
   virtual ~Motor();

   // Sets the speed of the motor.
   void setSpeed(
      // The speed of the motor.
      // Positive values indicate the montor is running forward; negative values reverse.
      int speed);

   // Retrieves the speed of the motor.
   int getSpeed() const;

   // This operation should be called on startup to prepare the sensor for polling/updating.
   virtual void setup();

   // This operation should be called continuously from within the main control loop.
   virtual void run();

   // This operation handles a message directed to this sensor.
   virtual bool handleMessage(
      // The message to handle.
      const Message& message);

   static const int MIN_SPEED = 0;

   static const int MAX_SPEED = 1023;

private:

   // Updates the speed and direction GPIO pins to reflect the current motor speed.
   void updatePins();

   void directionPin(
      const int& value);

   void speedPin(
      const int& value);

   // The GPIO pin attached to the vibration sensor.
   int directionPinId;

   // The GPIO pin attached to the vibration sensor.
   int speedPinId;

   // The speed of the motor.
   // Positive values indicate the montor is running forward; negative values reverse.
   int speed;
};

inline Motor::~Motor()
{
   // Nothing to do here.
}

inline int Motor::getSpeed() const
{
   return (speed);
}

#endif  // MOTOR_H_INCLUDED
