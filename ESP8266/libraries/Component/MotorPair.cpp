// *****************************************************************************
// *****************************************************************************
// MotorPair.cpp
//
// Author: Jason Tost
// Date:   3.30.2016
//
// *****************************************************************************
// *****************************************************************************

#include "MotorPair.h"

const int MotorPair::MIN_SPEED;

const int MotorPair::MAX_SPEED;

const int MotorPair::MIN_YAW;

const int MotorPair::MAX_YAW;

MotorPair::MotorPair(
   const String& id,
   const Motor& leftMotor,
   const Motor& rightMotor) : Component(id)
{
   this->leftMotor = leftMotor;
   this->rightMotor = rightMotor;
}

void MotorPair::drive(
   int speed,
   int yaw)
{
   this->speed = contrain(speed, MIN_SPEED, MAX_SPEED);
   this->yaw = contrain(speed, MIN_YAW, MAX_YAW);

   updateMotors();
}

void MotorPair::setup()
{
}

void MotorPair::run()
{

}

bool MotorPair::handleMessage(
   const Message& message)
{
   bool handled = false;

   return (handled);
}

void MotorPair::updateMotors()
{
   int leftMotorSpeed = speed;
   int rightMotorSpeed = speed;

   if (yaw < 0)
   {
      // Cause the motor pair to yaw to the left by decreasing the speed of the left motor.
      leftMotorSpeed = ((rightMotorSpeed * abs(yaw)) / 100);
   }
   else if (yaw > 0)
   {
      // Cause the motor pair to yaw to the right by decreasing the speed of the right motor.
      rightMotorSpeed = ((leftMotorSpeed * yaw) / 100);
   }

   leftMotor.drive(leftMotorSpeed);
   rightMotor.drive(rightMotorSpeed);
}
