// *****************************************************************************
// *****************************************************************************
// Motor.cpp
//
// Author: Jason Tost
// Date:   12.10.2015
//
// *****************************************************************************
// *****************************************************************************

#include <Arduino.h>
#include "Esp8266.h"
#include "Motor.h"

Motor::Motor(
   const String& id,
   const int& directionPinId,
   const int& speedPinId) : Component(id)
{
   this->directionPinId = directionPinId;
   this->speedPinId = speedPinId;
}

void Motor::setSpeed(
   int speed)
{
   this->speed = speed;

   updatePins();
}

void Motor::setup()
{
   Pin* pin = Esp8266::getInstance()->getPin(directionPinId);
   if (pin)
   {
      pin->setMode(OUTPUT);
   }

   pin = Esp8266::getInstance()->getPin(speedPinId);
   if (pin)
   {
      pin->setMode(OUTPUT);
   }
}

void Motor::run()
{

}

bool Motor::handleMessage(
   const Message& message)
{

}

void Motor::updatePins()
{
   if (speed == 0)
   {
      directionPin(LOW);
      speedPin(MIN_SPEED);
   }
   else if (speed > 0)
   {
      directionPin(HIGH);
      speedPin(MAX_SPEED - speed);
   }
   else // if (speed < 0)
   {
      directionPin(LOW);
      speedPin(abs(speed));
   }
}

void Motor::directionPin(
   const int& value)
{
   Pin* pin = Esp8266::getInstance()->getPin(directionPinId);

   if (pin)
   {
      pin->digitalWrite(value);
   }
}

void Motor::speedPin(
   const int& value)
{
   Pin* pin = Esp8266::getInstance()->getPin(speedPinId);

   if (pin)
   {
      pin->analogWrite(value);
   }
}
