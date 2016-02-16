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
#include "Logger.h"
#include "MessageRouter.h"
#include "Messages.h"
#include "Motor.h"

const int Motor::MIN_SPEED;

const int Motor::MAX_SPEED;

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
   bool handled = false;

   // MOTOR_CONFIG
   if (message.getMessageId() == MotorConfigMsg::MESSAGE_ID)
   {
      Logger::logDebug("Motor Config\n");

      handled = true;

      const MotorConfigMsg* castMessage = static_cast<const MotorConfigMsg*>(&message);

      // speed
      speed = castMessage->getSpeed();

      Logger::logDebug("Speed = " + String(speed) + "\n");

      updatePins();

      Message* replyMessage = new MotorConfigReplyMsg(speed);
      replyMessage->address(getId(), message.getSource());
      MessageRouter::getInstance()->sendMessage(*replyMessage);
   }

   return (handled);
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
      Logger::logDebug("Direction pin[" + String(pin->getPinId()) + "] = " + String(value) + "\n");
   }
}

void Motor::speedPin(
   const int& value)
{
   Pin* pin = Esp8266::getInstance()->getPin(speedPinId);

   if (pin)
   {
      pin->analogWrite(value);
      Logger::logDebug("Speed pin[" + String(pin->getPinId()) + "] = " + String(value) + "\n");
   }
}
