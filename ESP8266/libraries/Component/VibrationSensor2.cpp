// *****************************************************************************
// *****************************************************************************
// VibrationSensor2.cpp
//
// Author: Jason Tost
// Date:   10.29.2015
//
// *****************************************************************************
// *****************************************************************************

#include "Esp8266.h"
#include "Logger.h"
#include "MessageRouter.h"
#include "Messages.h"
#include "SensorUpdateMsg.h"
#include "VibrationSensor2.h"

const int MILLISECONDS_PER_SECOND = 1000;

VibrationSensor2::VibrationSensor2(
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

   stateChangeTime = millis();
}

VibrationSensor2::~VibrationSensor2()
{
}

void VibrationSensor2::setup()
{
   intervalTimer.setDelay(INTERVAL_TIME);
   intervalTimer.start();

   updateTimer.setDelay(UPDATE_TIME);
   updateTimer.start();
}

void VibrationSensor2::run()
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

   // Periodically update the server with the overall vibration state.
   if (updateTimer.isExpired())
   {
      // Send an update to the server.
      if (serverId != "")
      {
         SensorUpdateMsg message(getId(), state, ((millis() - stateChangeTime) / MILLISECONDS_PER_SECOND));
         message.address(getId(), serverId);
         MessageRouter::getInstance()->sendMessage(message);
      }

      updateTimer.start();
   }

   // Periodically calculate the overall vibration state.
   if (intervalTimer.isExpired())
   {
      // Increment the position in the circular queue.
      queuePosition++;
      if (queuePosition >= getIntervalCount())
      {
         // Wraparound.
         queuePosition = 0;
      }

      // Record the number of detected vibrations for this interval.
      queue[queuePosition] += vibrationCount;

      // Calculate the total number of detected vibrations over all the observed intervals.
      int total = 0;
      for (int i = 0; i < getIntervalCount(); i++)
      {
        total += queue[i];
      }

      // Calculate the new overall vibration state.
      bool prevState = state;
      state = (total > getVibrationThreshold());

      // Respond to state changes.
      if (prevState != state)
      {
         // Send an update to the server.
         if (serverId != "")
         {
            SensorUpdateMsg message(getId(), state, 0);
            message.address(getId(), serverId);
            MessageRouter::getInstance()->sendMessage(message);
         }

         // Record the state change time.
         stateChangeTime = millis();
      }

      // Reset for the next interval.
      vibrationCount = 0;
      intervalTimer.start();
   }
}

bool VibrationSensor2::handleMessage(
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
         setId(castMessage->getSensorId());
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
         responsiveness = castMessage->getSensitivity();
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
