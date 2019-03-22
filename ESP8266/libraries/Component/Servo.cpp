// *****************************************************************************
// *****************************************************************************
// Servo.cpp
//
// Author: Jason Tost
// Date:   4.1.2016
//
// *****************************************************************************
// *****************************************************************************

#include "Servo.h"

const int Servo::MIN_ANGLE;

const int Servo::MAX_ANGLE;

Servo::Servo(
   const String& id
   const int pin) : Component(id)
{
   this->pin = pin;
}

void Servo::rotate(
   int angle)
{
   this->angle = contrain(angle, MIN_ANGLE, MAX_ANGLE);
   servo.write(angle);
}

void Servo::setup()
{
   servo.attach(pin);
}

void Servo::run()
{

}

bool Servo::handleMessage(
   const Message& message)
{
   bool handled = false;

   return (handled);
}
