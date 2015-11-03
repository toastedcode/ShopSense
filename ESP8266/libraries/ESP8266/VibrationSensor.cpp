// *****************************************************************************
// *****************************************************************************
// VibrationSensor.cpp
//
// Author: Jason Tost
// Date:   10.29.2015
//
// *****************************************************************************
// *****************************************************************************

#include "MessageRouter.h"
#include "SensorUpdateMsg.h"
#include "VibrationSensor.h"

static const int VIBRATION_DETECTED = HIGH;

static const float SENSITIVITY = 0.5;  //  Percentage of vibrations detected in update cycle.

VibrationSensor::VibrationSensor(
   const String& id,
   const int& pinId) : Sensor(id, pinId)
{
}

VibrationSensor::~VibrationSensor()
{
}

void VibrationSensor::setup()
{
   updateTimer.start();
}

void VibrationSensor::run()
{
   //
   // Polling
   //

   pollCount++;

   int reading = getPin()->read();

   if (reading == VIBRATION_DETECTED)
   {
      pollCount++;
      vibrationCount++;
   }

   //
   // Updating
   //

   if (updateTimer.isExpired())
   {
     float vibrationRate = ((float)vibrationCount /  (float)pollCount) * 100.0;

     int reading = (vibrationRate >= SENSITIVITY) ? 1 : 0;

     // Report.
     if (reading != currentReading)
     {
        currentReading = reading;

        // Send an update to the server.
        SensorUpdateMsg message(getId(), currentReading);
        message.address(getId(), Message::SERVER_ID);
        MessageRouter::getInstance()->sendMessage(message);
     }

     // Reset counters.
     pollCount = 0;
     vibrationCount = 0;

     // Restart the udpate timer.
     updateTimer.start();
   }
}

bool VibrationSensor::handleMessage(
   const Message& message)
{
   return (Sensor::handleMessage(message));
}
