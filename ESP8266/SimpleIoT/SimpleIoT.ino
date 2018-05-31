// *****************************************************************************
// *****************************************************************************
// SimpleIoT.ino
//
// Author: Jason Tost
// Date:   10.29.2015
//
// *****************************************************************************
// *****************************************************************************

#include <ButtonSensor.h>
#include <ESP8266.h>
#include <ESP8266WiFi.h>
#include <HttpProtocol.h>
#include <MessageRouter.h>
#include <SerialLogger.h>
#include <VibrationSensor.h>
#include <WebAdapter.h>

// *****************************************************************************
//                               Global variables
// *****************************************************************************

static const String SSID = "REDACTED"; 
static const String PASSWORD = "REDACTED";
//static const String SENSOR_NAME = "button_01";
static const String SENSOR_NAME = "vibration_01";
static const int SENSOR_PIN = 2;
static const int UPDATE_RATE = 5000;  // 1 second

//ButtonSensor sensor(SENSOR_NAME, SENSOR_PIN);
VibrationSensor sensor(SENSOR_NAME, SENSOR_PIN);

WebAdapter serverAdapter(SERVER_ID);

HttpProtocol serverProtocol;

// *****************************************************************************
//                               Arduino functions
// *****************************************************************************

void setup()
{
  Serial.begin(9600);
 
  Logger::setLogger(new SerialLogger());

  Logger::logDebug("********************************\n");
  Logger::logDebug("********** Simple IoT **********\n");
  Logger::logDebug("********************************\n");
  Logger::logDebug("\n");
  
  Esp8266::getInstance()->connectWifi(SSID, PASSWORD);

  // Configure the adapter we'll use to communicate with the server.
  serverAdapter.setProtocol(serverProtocol);
  serverAdapter.setServerAddress("www.roboxes.com");
  serverAdapter.setServerPage("shopSense.php");
  MessageRouter::getInstance()->registerAdapter(serverAdapter);

  // Configure the sensor.
  sensor.setUpdateRate(UPDATE_RATE);
  MessageRouter::getInstance()->registerHandler(sensor);

  sensor.setup();
}

void loop()
{
  MessageRouter::getInstance()->run();
  
  sensor.run();
}
