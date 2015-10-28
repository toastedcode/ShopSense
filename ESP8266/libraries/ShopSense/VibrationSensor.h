// *****************************************************************************
// *****************************************************************************
// VibrationSensor.h
//
// Author: Jason Tost
// Date:   10.27.2015
//
// Inspired by code at https://github.com/amiravni/ESP8266-Water-Heater-Control/blob/master/TheDude.ino
//
// *****************************************************************************
// *****************************************************************************

#ifndef VIBRATIONSENSOR_H_INCLUDED
#define VIBRATIONSENSOR_H_INCLUDED

#include "Common.h"
#include "Config.h"
#include "Pin.h"
#include "Timer.h"

class VibrationSensor
{

public:
   
   // Constructor.
   VibrationSensor();

   // Destructor.
   virtual ~VibrationSensor();

   // This operation is run on startup to prepare the sensor for polling.
   virtual void setup();

   // This operation should be run from within the main control loop.
   virtual void run();

   // Sets the sensivity of the vibration sensor.
   void setSensitivity(
      // A value from 0 to 100 specifying the sensor sensitivity.
      int sensitivity);

private:
   
   // This operation connects to the Wifi network specified in the sensor config.
   // True is returned if the connection was made; false otherwise.
   bool connectWifi();

   // This operation takes a reading from the defined sensor pin.
   virtual int read();
   
   // This operation sends the specified sensor reading using the current sensor configuration.
   void sendReading(int reading);

   static const int MIN_SENSITIVITY = 1;

   static const int MAX_SENSITIVITY = 100;

   // The pin that will be used to for reading and writing to the sensor.
   Pin sensorPin = Pin(SENSOR_PIN_ID);

   // A flag indicating if the sensor is connected to the wifi network.
   bool isConnected = false;

   // A flag indicating if the sensor has up to date configuration data.
   bool isConfigured = false;

   // The current sensor configuration data.
   Config config;

   // A value used in determining the responsiveness of the sensor.
   // 1 = least sensitive.
   // 100 = most sensitive.
   int sensitivity = 0;

   // The timer used in timing the sensor polling.
   Timer pollTimer;

   // A timer used in timing the sensor reading calculations and updating.
   Timer updateTimer;

   // A count of sensor pollings, per update cycle.
   int pollCount;

   // A count of measured vibrations, per update cycle.
   int vibrationCount = 0;

   // The last reading reported by this sensor.
   int currentReading = 0;
};

inline void VibrationSensor::setSensitivity(
   int sensitivity)
{
   this->sensitivity = sensitivity;
}

#endif  // VIBRATIONSENSOR_H_INCLUDED
