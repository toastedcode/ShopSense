// *****************************************************************************
// *****************************************************************************
// ShopSense.ino
//
// Author: Jason Tost
// Date:   9.23.2015
//
// Inspired by code at https://github.com/amiravni/ESP8266-Water-Heater-Control/blob/master/TheDude.ino
//
// *****************************************************************************
// *****************************************************************************

#include <ESP8266WiFi.h>

// Uncomment to enable serial debug
#define DEBUG 1

// Macro for debug printing.
#define printDebug(str) {if (DEBUG) Serial.print(str);}

// *****************************************************************************
//                               Global constants

// Pin ids for the ESP8266.
// Connect GPIO 1 to sensor.
// Connect GPIO 2 to ground via hardware reset button.
const int SENSOR_PIN_ID = 1;
const int RESET_PIN_ID = 2;

// *****************************************************************************
//                               Class definitions

// A class representing a GPIO pin on an ESP8266 module.
class Pin
{

public:

   // Constructor.
   Pin(int pinId)
   {
      this->pinId = pinId;
   }

   // This operation reads from the sensor pin and returns the current value.   
   int read()
   {
      return (digitalRead(pinId));
   }
   
   // This operation writes the specified value to the sensor pin.
   int write(int value)
   {
      pinMode(pinId, OUTPUT);
      digitalWrite(pinId, value);
   }
   
   // TODO: Interrupt
   
private:
   
   // The GPIO pin (1 or 2) represented by this class.
   int pinId;
};

// A structure containing sensor configuration data.
struct Config
{
   // The SSID of the Wifi network to which this sensor should connect.
   const char* ssid = "";
   
   // The password that this sensor should use in connecting to the Wifi network.
   const char* password = "";
   
   // The unique sensor name to be used when posting readings to the server.
   const char* sensorName = "";
   
   // The sensor polling and reporting rate.
   int pollRate = 0;
   
   // The address of the sensor server.
   const char* serverAddress = "";
};

// A class used in timing operations within the sensor.
class Timer
{

public:

   // This operation starts the timer.
   void start(
      // The delay (in milliseconds) of the timer.
      int delay)
   {
      this->delay = delay;
      startTime = millis();
   }

   // This operation return true if the timer has expired.
   bool isExpired()
   {
      return ((startTime != 0) &&
              ((millis() - startTime) > delay));
   }
   
private:

   // The delay (in milliseconds) associated with this timer.
   int delay;

   // The time at which this timer was started.
   int startTime;
};

// A class representing the sensor and all its functions.
class Sensor
{

public:

   // This operation is run on startup to prepare the sensor for polling.
   void setup()
   {
      // TODO: Configure via Web server.
      config.ssid = "NETGEAR69";
      config.password = "silentsky723";
      config.sensorName = "vibration_01";
      config.pollRate = 5000;
      config.serverAddress = "www.roboxes.com";
      isConfigured = true;
   
      // Connect to the Wifi network
      connectWifi();
      
      // Start our polling timer.
      pollTimer.start(config.pollRate);
   }

   // This operation should be run from within the main control loop.   
   void run()
   {
      // Loop indefinitely.
      while (true)
      {
         if (isConfigured)
         {
            if (pollTimer.isExpired())
            {
               printDebug("Polling ...\n");
               
               // Read from the sensor.
               int reading = sensorPin.read();
            
               // Send an update to the server.
               sendReading(reading);
               
               // Restart the poll timer.
               pollTimer.start(config.pollRate);
            }
         }
      }
   }
   
private:

   // This operation connects to the Wifi network specified in the sensor config.
   // True is returned if the connection was made; false otherwise.
   bool connectWifi()
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

   // This operation sends the specified sensor reading using the current sensor configuration.
   void sendReading(int reading)
   {
      if (isConfigured)
      {
         printDebug("Sending sensor reading [");
         printDebug(reading);
         printDebug("] to sensor server at ");
         printDebug(config.serverAddress);
         printDebug(".\n");
      }
   }

   // The pin that will be used to for reading and writing to the sensor.
   Pin sensorPin = Pin(SENSOR_PIN_ID);

   //  The pin that will be used to reset the module.
   Pin resetPin = Pin(RESET_PIN_ID);
   
   // A flag indicating if the sensor is connected to the wifi network.
   bool isConnected = false;

   // A flag indicating if the sensor has up to date configuration data.
   bool isConfigured = false;
   
   // The current sensor configuration data.
   Config config;
   
   // The timer used in timing the sensor polling and reporting.
   Timer pollTimer;
};

// *****************************************************************************
//                               Global variables
// *****************************************************************************

// Our sensor.
Sensor sensor;

// *****************************************************************************
//                               Arduino functions
// *****************************************************************************

void setup()
{
   sensor.setup();
}

void loop()
{
   sensor.run();
}
