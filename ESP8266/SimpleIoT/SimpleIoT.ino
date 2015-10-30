// *****************************************************************************
// *****************************************************************************
// SimpleIoT.ino
//
// Author: Jason Tost
// Date:   10.29.2015
//
// *****************************************************************************
// *****************************************************************************

#include <ESP8266.h>
#include <ESP8266WiFi.h>
#include <ButtonSensor.h>
#include <SerialLogger.h>
#include <VibrationSensor.h>

// *****************************************************************************
//                               Global variables
// *****************************************************************************

static const String SSID = "NETGEAR69"; 
static const String PASSWORD = "silentsky723";
static const String SENSOR_NAME = "button_01";
static const int SENSOR_PIN = 2;
static const int UPDATE_RATE = 1000;  // 1 second

Sensor* sensor;

// *****************************************************************************
//                               Arduino functions
// *****************************************************************************

void setup()
{
  Serial.begin(9600);
  Serial.println("Starting ... \n\n");
  
  Logger::setLogger(new SerialLogger());

  Logger::logDebug("********************************\n");
  Logger::logDebug("********** Simple IoT **********\n");
  Logger::logDebug("********************************\n");
  Logger::logDebug("\n");
  
  Esp8266::getInstance()->connectWifi(SSID, PASSWORD);

  sensor = new ButtonSensor(SENSOR_NAME, SENSOR_PIN);
  sensor->setUpdateRate(UPDATE_RATE);

  sensor->setup();
}

void loop()
{
  sensor->run();
}
