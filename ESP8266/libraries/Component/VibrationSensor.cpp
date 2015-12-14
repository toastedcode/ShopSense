// *****************************************************************************
// *****************************************************************************
// VibrationSensor.cpp
//
// Author: Jason Tost
// Date:   10.29.2015
//
// *****************************************************************************
// *****************************************************************************

#include <Arduino.h>
#include "Esp8266.h"
#include "Logger.h"
#include "MessageRouter.h"
#include "Messages.h"
#include "SensorUpdateMsg.h"
#include "VibrationSensor.h"

VibrationSensor::VibrationSensor(
   const String& id,
   const int& pinId) : Component(id)
{
   this->pinId = pinId;
   sensitivity = DEFAULT_SENSITIVITY;
   responsiveness= DEFAULT_RESPONSIVENESS;

   vibrationCount = 0;

   for (int i = 0; i < NUM_INTERVALS; i++)
   {
     queue[i] = NOT_VIBRATING;
   }

   Pin* pin = Esp8266::getInstance()->getPin(pinId);
   if (pin)
   {
      pin->setMode(INPUT);
   }
}

VibrationSensor::~VibrationSensor()
{
}

void VibrationSensor::setup()
{
   intervalTimer.setDelay(INTERVAL_TIME);
   intervalTimer.start();
}

void VibrationSensor::run()
{
   // Take a reading.
   int lastReading = reading;
   Pin* pin = Esp8266::getInstance()->getPin(pinId);
   if (pin)
   {
      reading = pin->read();
   }

   // Each change shall be recorded as a discrete vibration.
   if (reading != lastReading)
   {
      vibrationCount++;
   }

   if (intervalTimer.isExpired())
   {
      // Increment the position in the circular queue.
      queuePosition++;
      if (queuePosition >= NUM_INTERVALS)
      {
         // Wraparound.
         queuePosition = 0;
      }

      // Record the vibrating state for this interval.
      // TODO: Use senstivity value.
      queue[queuePosition] = (vibrationCount > 0) ? VIBRATING : NOT_VIBRATING;

      // Calculate the overall vibrating state.
      // TODO: Use responsiveness value.
      int total = 0;
      for (int i = 0; i < NUM_INTERVALS; i++)
      {
        total += queue[i];
      }

      bool prevState = state;
      state = (total > (NUM_INTERVALS / 2));

      // Respond to state changes.
      if (prevState != state)
      {
         //digitalWrite(ledPin, state);

         // Send an update to the server.
         /*
         SensorUpdateMsg message(getId(), currentReading);
         message.address(getId(), SERVER_ID);
         MessageRouter::getInstance()->sendMessage(message);
         */
         Logger::logDebug("State = " + String(state) + "\n");
      }

      // Reset for the next interval.
      vibrationCount = 0;
      intervalTimer.start();
   }
}

bool VibrationSensor::handleMessage(
   const Message& message)
{
   bool handled = false;

   // VIBRATION_SENSOR_CONFIG
   if (message.getMessageId() == VibrationSensorConfigMsg::MESSAGE_ID)
   {
      Logger::logDebug("Vibration Sensor Config\n");

      handled = true;

      const VibrationSensorConfigMsg* castMessage = static_cast<const VibrationSensorConfigMsg*>(&message);

      // sensorId
      if (castMessage->getSensorId() != "")
      {
         // TODO
      }

      // serverIpAddress
      if (castMessage->getServerIpAddress() != "")
      {
         // TODO
      }

      // sensitivity
      if (castMessage->getSensitivity() != 0)
      {
         sensitivity = castMessage->getSensitivity();
      }

      // responsiveness
      if (castMessage->getResponsiveness() != 0)
      {
         sensitivity = castMessage->getSensitivity();
      }

      // isEnabled
      // TODO

      Message* replyMessage = new VibrationSensorConfigReplyMsg(getId(),
                                                                "",              // serverIpAddress TODO
                                                                sensitivity,
                                                                responsiveness,
                                                                true,            // isEnabled  TODO
                                                                true);           // success
      replyMessage->address(getId(), message.getSource());
      MessageRouter::getInstance()->sendMessage(*replyMessage);
   }

   return (handled);
}
