// *****************************************************************************
// *****************************************************************************
// MqttAdapter.cpp
//
// Author: Jason Tost
// Date:   2.12.2016
//
// *****************************************************************************
// *****************************************************************************

#include "Logger.h"
#include "Utility.h"
#include "MqttAdapter.h"

WiFiClient MqttAdapter::client;

PubSubClient MqttAdapter::mqttClient(client);

typedef void (*MqttCallbackFunction)(char*, unsigned char*, unsigned int);

MqttAdapter::MqttAdapter(
   const String& id) : Adapter(id)
{
   serverAddress = "";

   // TODO: Have to solve this.  Can't pass member function as parameter.
   //mqttClient.setCallback(callback);

   // Attempt our first connection to the broker.
   connect();
}

MqttAdapter::~MqttAdapter()
{
}

bool MqttAdapter::sendMessage(
   const Message& message)
{
   bool messageSent = false;

   String serializedMessage;

   if ((protocol != 0) &&
       (protocol->serialize(message, serializedMessage) == true))
   {
      if (mqttClient.connected() || connect())
      {
         // Construct the topic.
         // Ex. mycompany.com/sensors/vibration_01/reading
         String topic = publishTopic + "/" + message.getSource() + "/" + toString(message.getMessageId());

         // Publish to the MQTT broker.
         mqttClient.publish(publishTopic.c_str(), serializedMessage.c_str());
      }
      else
      {
         Logger::logDebug("Failed to send message " + toString(message.getMessageId()) + ".\n");
      }
   }
   else
   {
      Logger::logDebug("Failed to serialize message " + toString(message.getMessageId()) + ".\n");
   }

   return (messageSent);
}

const Message* MqttAdapter::getMessage()
{
   Message* message = 0;

   // Let the MQTT client listen for connections and fill the message queue.
   mqttClient.loop();

   // Return the top message, if one exists.
   return (messageQueue.pop());
}


bool MqttAdapter::connect()
{
  if (!mqttClient.connected())
  {
     Logger::logDebug("Attempting MQTT connection ... ");

     if (mqttClient.connect("MQTTClient"))  // TODO Configured client handle.
     {
        Logger::logDebug("success!\n");

       // Subscribe to posts.
       // subscribe()
     }
     else
     {
        Logger::logDebug("failed!\n");
     }
   }

  return (mqttClient.connected());
}

void MqttAdapter::callback(
   char* topic,
   unsigned char* payload,
   unsigned int length)
{
   static const int BUFFER_SIZE = 256;
   static char buffer[BUFFER_SIZE];

   if (length < BUFFER_SIZE)
   {
      // Convert the payload into a String.
      memcpy(buffer, payload, length);
      buffer[BUFFER_SIZE - 1] = 0;
      String messageString(buffer);

      // Parse the message.
      Message* message = 0;
      protocol->parse(messageString, message);

      // Add to message queue.
      if (message)
      {
         messageQueue.push(message);
      }
   }
   else
   {
      Logger::logDebug("Message too long.\n");
   }
}

void MqttAdapter::parseTopic(
   const String& topic,
   String& componentId,
   String& messageId)
{

}
