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
   const String& sensorId,
   const int& pinId) : Sensor(sensorId, pinId)
{
}

VibrationSensor::~VibrationSensor()
{
}

void VibrationSensor::setup()
{
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
        SensorUpdateMsg message(sensorId, MessageRouter::SERVER_ID, currentReading);
        MessageRouter::sendMessage(&message);
     }

     // Reset counters.
     pollCount = 0;
     vibrationCount = 0;

     // Restart the udpate timer.
     updateTimer.restart();
   }
}

void VibrationSensor::handleMessage(
   const Message* message)
{
   Sensor::handleMessage(message);
}
