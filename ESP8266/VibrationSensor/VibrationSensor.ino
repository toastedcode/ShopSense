// *****************************************************************************
// *****************************************************************************
// VibrationSensor.ino
//
// Author: Jason Tost
// Date:   12.1.2015
//
// *****************************************************************************
// *****************************************************************************

#include <ArduinoJson.h>
#include <DweetProtocol.h>
#include <ESP8266.h>
#include <ESP8266WiFi.h>
#include <JsonProtocol.h>
#include <Logger.h>
#include <MessageHandler.h>
#include <MessageRouter.h>
#include <MqttAdapter.h>
#include <PubSubClient.h>
#include <QueueList.h>
#include <Timer.h>
#include <ToastBot.h>
#include <Utility.h>
#include <VibrationSensor.h>
#include <VibrationSensor2.h>
#include <WebClientAdapter.h>
#include <WebServerAdapter.h>
#include <WebTime.h>

// *****************************************************************************
//                               Global variables
// *****************************************************************************

const String DWEET_SERVER_ADDRESS = "dweet.io";
const String MQTT_SERVER_ADDRESS = "test.mosquitto.org";

VibrationSensor2 sensor("pptp_machine01_vibration", 14);

//DweetProtocol dweetProtocol;

JsonProtocol jsonProtcol;

//WebClientAdapter dweetAdapter(DWEET_SERVER_ADDRESS);
MqttAdapter mqttAdapter(MQTT_SERVER_ADDRESS);

// *****************************************************************************
//                               Arduino functions
// *****************************************************************************

void setup()
{
  Serial.begin(9600);
  
  ToastBot::getInstance()->begin();

  sensor.setup();

  //sensor.setServerId(DWEET_SERVER_ADDRESS);
  sensor.setServerId(MQTT_SERVER_ADDRESS);

  MessageRouter::getInstance()->registerHandler(sensor);

  //dweetAdapter.setProtocol(dweetProtocol);
  //dweetAdapter.setServerAddress(DWEET_SERVER_ADDRESS);
  //MessageRouter::getInstance()->registerAdapter(dweetAdapter);

  mqttAdapter.setProtocol(jsonProtcol);
  mqttAdapter.setServerAddress(MQTT_SERVER_ADDRESS, 1883);
  mqttAdapter.setPublishTopic("pittsburghprecision.com/sensors/");
  MessageRouter::getInstance()->registerAdapter(mqttAdapter);
}

void loop()
{
  ToastBot::getInstance()->run();

  sensor.run();
}
