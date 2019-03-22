// *****************************************************************************
// *****************************************************************************
// MotorPair.h
//
// Author: Jason Tost
// Date:   3.30.2016
//
// *****************************************************************************
// *****************************************************************************

#ifndef MOTORPAIR_H_INCLUDED
#define MOTORPAIR_H_INCLUDED

#include "Motor.h"
#include "Timer.h"

class MotorPair : public Component
{

public:
   
   // Constructor.
   MotorPair(
      // A unique identifier for this component.
      const String& id,
      // The left motor in a motor pair.
      const Motor& leftMotor,
      // The right motor in a motor pair.
      const Motor& rightMotor);

   // Destructor.
   virtual ~MotorPair();

   /*
   // Sets the speed of the two motors in the pair.
   void drive(
      // The speed of the left motor in the pair.
      // Positive values indicate the motor is running forward; negative values reverse.
      int leftSpeed,
      // The speed of the left motor in the pair.
      // Positive values indicate the motor is running forward; negative values reverse.
      int rightSpeed);
   */

   // Sets the speed of the two motors in the pair.
   void drive(
      // The speed of the left motor in the pair.
      // Positive values indicate the motor is running forward; negative values reverse.
      int speed,
      // The speed ratio between the left and right motors.
      // Positive values indicate the motor pair will be turning to the right; negative values left.
      int yaw);

   // Stops both motors in the pair by setting their speed to zero.
   void stop();

   // Retrieves the speed of the motor pair.
   int getSpeed() const;

   // Retrieves the yaw of the motor pair.
   int getYaw() const;

   // This operation should be called on startup to prepare the sensor for polling/updating.
   virtual void setup();

   // This operation should be called continuously from within the main control loop.
   virtual void run();

   // This operation handles a message directed to this sensor.
   virtual bool handleMessage(
      // The message to handle.
      const Message& message);

   static const int MIN_SPEED = -1023;

   static const int MAX_SPEED = 1023;

   static const int MIN_YAW = -100;

   static const int MAX_YAW = 100;

private:

   // Updates the two motors to reflect the current speed.
   void updateMotors();

   // The left motor in a motor pair.
   Motor leftMotor;

   // The right motor in a motor pair.
   Motor rightMotor;

   // The speed of the motor pair.
   // Positive values indicate the motors are running forward; negative values reverse.
   int speed;

   // The speed ratio between the left and right motors.
   // Positive values indicate the motor pair will be turning to the right; negative values left.
   int yaw;
};

inline MotorPair::~MotorPair()
{
   // Nothing to do here.
}

inline int MotorPair::getSpeed() const
{
   return (speed);
}

inline int MotorPair::getYaw() const
{
   return (yaw);
}

#endif  // MOTORPAIR_H_INCLUDED
