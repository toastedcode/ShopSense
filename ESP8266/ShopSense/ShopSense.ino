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
const int SENSOR_PIN_ID = 2;
const int RESET_PIN_ID = 0;

// HTTP port
const int HTTP_PORT = 80;

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
      pinMode(pinId, INPUT);
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
   
   // The unique sensor id to be used when posting readings to the server.
   const char* sensorId = "";

   // The rate (in milliseconds) at which the sensor will be read.
   int readingRate = 0;
   
   // The rate (in milliseconds) at which the average reading will be sent to the server.
   int pollRate = 0;

   // A flag indicating if the sensor should only report changed sensor values.
   bool reportOnChanged = false;
   
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
      config.sensorId = "vibration_01";
      config.readingRate = 100;
      config.pollRate = 1000;
      config.reportOnChanged = true;
      config.serverAddress = "www.roboxes.com";
      isConfigured = true;
   
      // Connect to the Wifi network
      connectWifi();
      
      // Start our timers.
      readingTimer.start(config.readingRate);
      pollTimer.start(config.pollRate);
   }

   // This operation should be run from within the main control loop.   
   void run()
   {
       if (isConfigured)
       {
          if (readingTimer.isExpired())
          {
             //printDebug("Reading ...\n");
             
             // Read from the sensor.
             int reading = sensorPin.read();

             // Compute the running sum.
             readingSum += reading;
            
             // Restart the reading timer.
             readingTimer.start(config.readingRate);
          }

          if (pollTimer.isExpired())
          {
             printDebug("Polling ...\n");
             
             int averageReading = int(((float)readingSum / (float)(config.pollRate / config.readingRate)) + 0.5);

             printDebug("Sum = " + String(readingSum) + "; average = " + String(averageReading) + "\n");
            
             if ((config.reportOnChanged == false) ||
                 (averageReading != lastReading))
             {
                // Send an update to the server.
                sendReading(averageReading);
             }

             lastReading = averageReading;
             readingSum = 0;

             // Restart the poll timer.
             pollTimer.start(config.pollRate);
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

   // The timer used in timing the sensor readings.
   Timer readingTimer;
   
   // The timer used in timing the sensor polling and reporting.
   Timer pollTimer;

   // A running sum of sensor readings that will be used to compute an average.
   int readingSum = 0;

   // The last reading reported by this sensor.
   int lastReading = 0;
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
   Serial.begin(9600);

   printDebug("setup\n");
   sensor.setup();
}

void loop()
{
   sensor.run();

   delay(10);
}
