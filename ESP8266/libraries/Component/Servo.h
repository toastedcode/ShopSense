// *****************************************************************************
// *****************************************************************************
// MotorPair.h
//
// Author: Jason Tost
// Date:   3.30.2016
//
// *****************************************************************************
// *****************************************************************************

#ifndef SERVO_H_INCLUDED
#define SERVO_H_INCLUDED

#include <SoftwareServo.h>

class Servo : public Component
{

public:
   
   // Constructor.
   Servo(
      // A unique identifier for this component.
      const String& id,
      // The control pin for the servo.
      const int& pin);

   // Destructor.
   virtual ~Servo();

   // Sets the speed of the two motors in the pair.
   void rotate(
      // The angle the servo should rotate to.
      int angle);

   // Retrieves the current angle of the servo.
   int getAngle() const;

   // This operation should be called on startup to prepare the sensor for polling/updating.
   virtual void setup();

   // This operation should be called continuously from within the main control loop.
   virtual void run();

   // This operation handles a message directed to this sensor.
   virtual bool handleMessage(
      // The message to handle.
      const Message& message);

   static const int MIN_ANGLE = 0;

   static const int MAX_ANGLE = 180;

private:

   // A servo object from the Arduino library.
   SoftwareServo servo;

   // The angle of the servo.
   int angle;
};

inline Servo::~Servo()
{
   // Nothing to do here.
}

inline int Servo::getAngle() const
{
   return (angle);
}

#endif  // SERVO_H_INCLUDED
