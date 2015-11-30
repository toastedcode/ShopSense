#include <ESP8266WiFi.h>
#include <ESP8266.h>
#include <HttpProtocol.h>
#include <PingMsg.h>
#include <PingReplyMsg.h>
#include <MessageRouter.h>
#include <SerialAdapter.h>
#include <SerialLogger.h>
#include <Utility.h>
#include <WebControlAdapter.h>

static const String SSID = "NETGEAR69"; 
static const String PASSWORD = "silentsky723";

WebControlAdapter adapter("WEB_CONTROL_ADAPTER");
//SerialAdapter adapter("SERIAL_ADAPTER");

HttpProtocol protocol;

void setup()
{
   Serial.begin(9600);
   Serial.print("*** Ping Test ***\n");

   Logger::setLogger(new SerialLogger());

   Esp8266::getInstance()->connectWifi(SSID, PASSWORD);
   
   // Setup message listeners.
   Esp8266::getInstance()->setup();

   // Setup adapters.
   adapter.setProtocol(protocol);
   MessageRouter::getInstance()->registerAdapter(adapter);
   adapter.setup();
}

void loop()
{
  MessageRouter::getInstance()->run();
}
