// *****************************************************************************
// *****************************************************************************
// VibrationSensor.h
//
// Author: Jason Tost
// Date:   10.27.2015
//
// *****************************************************************************
// *****************************************************************************

#include "Arduino.h"
#include "Common.h"
#include "ESP8266WiFi.h"
#include "VibrationSensor.h"

static const int VIBRATION_DETECTED = HIGH;

// *****************************************************************************
//                                  Public
// *****************************************************************************

void VibrationSensor::setup()
{
   // TODO: Configure via Web server.
   config.ssid = "NETGEAR69";
   config.password = "silentsky723";
   config.sensorId = "vibration_01";
   config.pollRate = 10;
   config.updateRate = 1000;
   config.reportOnChanged = true;
   config.serverAddress = "www.roboxes.com";

   isConfigured = true;

   sensitivity = 50;

   // Connect to the Wifi network
   connectWifi();

   // Start our timers.
   pollTimer.start(config.pollRate);
   updateTimer.start(config.updateRate);
}

VibrationSensor::VibrationSensor()
{
}

VibrationSensor::~VibrationSensor()
{
}

void VibrationSensor::run()
{
   if (isConfigured)
   {
      //
      // Polling
      //

      if (pollTimer.isExpired())
      {
         pollCount++;

         int reading = read();

         if (reading == VIBRATION_DETECTED)
         {
            pollCount++;
            vibrationCount++;
         }

         // Restart the polling timer.
         pollTimer.start(config.pollRate);
      }

      //
      // Calculations and updating
      //

      if (updateTimer.isExpired())
      {
         float vibrationRate = ((float)vibrationCount /  (float)pollCount) * 100.0;

         int lastReading = currentReading;

         currentReading = (vibrationRate >= (MAX_SENSITIVITY - sensitivity)) ? 1 : 0;

         // Report.
         if ((config.reportOnChanged == false) ||
             (lastReading != currentReading))
         {
            // Send an update to the server.
            sendReading(currentReading);
         }

         // Reset counters.
         pollCount = 0;
         vibrationCount = 0;

         // Restart the udpate timer.
         updateTimer.start(config.updateRate);
      }
   }
}

// *****************************************************************************
//                                  Private
// *****************************************************************************

// This operation connects to the Wifi network specified in the sensor config.
// True is returned if the connection was made; false otherwise.
bool VibrationSensor::connectWifi()
{
   if (isConfigured)
   {
      printDebug("Connecting to Wifi network ");
      printDebug(config.ssid);
      printDebug("\n");

            WiFi.mode(WIFI_STA);
            WiFi.begin(config.ssid, config.password);

            int secondsToConnect = 0;

            // Wait for 30 seconds, or until the connection is made.
            while ((WiFi.status() != WL_CONNECTED) &&
                   (secondsToConnect < 30))
            {
               delay(1000);
               secondsToConnect++;
               printDebug(" .");
      }

      if (WiFi.status() == WL_CONNECTED)
      {
         isConnected = true;

         printDebug(" success!\n");
         printDebug(" Connected at ");
         printDebug(WiFi.localIP());
      }
      else
      {
         isConnected = true;

               printDebug(" failed!\n");
      }
   }

   return (isConnected);
}

int VibrationSensor::read()
{
   printDebug("Reading ...\n");

   // Read from the sensor.
   int reading = sensorPin.read();

   return (reading);
}

void VibrationSensor::sendReading(int reading)
{
   if (isConfigured && isConnected)
   {
      printDebug("Sending sensor reading [" + String(reading) + "] to sensor server at " + String(config.serverAddress) + ".\n");

      // Construct the HTTP GET request.
      String request = "GET /shopSense.php?command=data&sensor_id=" + String(config.sensorId) + "&sensor_reading=" + reading + " HTTP/1.0";
      printDebug("HTTP request = \"" + request + "\"\n");

      WiFiClient client;

      // Connect to the server.
      if (client.connect(config.serverAddress, HTTP_PORT) == false)
      {
         printDebug("Failed to connect to server.");
      }
      else
      {
         // Make the request.
         client.println(request);
         client.println("HOST: roboxes.com");
         client.println();

         // Read all the lines of the reply from server.
         while(client.available())
         {
            String line = client.readStringUntil('\r');
            printDebug(line);
         }
      }
   }
}
