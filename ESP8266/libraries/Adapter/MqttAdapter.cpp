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

MqttAdapter::MqttAdapter(
   const String& id) : Adapter(id)
{
   mqttClient.setCallback(this);
   subscriptions.reserve(10);
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
         String topic = publishTopic + message.getSource() + "/" + toString(message.getMessageId());

         Logger::logDebug("Publishing: " + topic + "/" + serializedMessage + "\n");

         // Publish to the MQTT broker.
         if (mqttClient.publish(topic.c_str(), serializedMessage.c_str()))
         {
            messageSent = true;
         }
         else
         {
            Logger::logDebug("Failed to publish.\n");
         }
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
   if (!messageQueue.isEmpty())
   {
      message = messageQueue.pop();
   }

   return (message);
}

void MqttAdapter::subscribe(
   const String& topic)
{
   subscriptions.push_back(topic);

   if ((mqttClient.connected()) &&
       (mqttClient.subscribe(topic.c_str())))
   {
      Logger::logDebug("Subscribed to \"" + topic + "\"\n");
   }
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

      Message* message = 0;
      String componentId = "";
      String messageId = "";

      // Parse the message.
      if ((parseTopic(topic, componentId, messageId)) &&
          (protocol->parse(messageString, message)))
      {
         // Add to message queue.
         message->address(getId(), componentId);
         messageQueue.push(message);
      }
      else
      {
         Logger::logDebug("Failed to parse message.\n");
      }
   }
   else
   {
      Logger::logDebug("Message too long.\n");
   }
}

bool MqttAdapter::connect()
{
  if (!mqttClient.connected())
  {
     Logger::logDebug("Attempting MQTT connection to " + serverAddress + ":" + String(port) + " ... ");

     mqttClient.setServer(serverAddress.c_str(), port);

     if (mqttClient.connect("MQTTClient"))  // TODO Configured client handle.
     {
        Logger::logDebug("success!\n");

        // Re-subscribe to posts.
        for (SimpleList<String>::iterator it = subscriptions.begin(); it != subscriptions.end(); it++)
        {
           mqttClient.subscribe(it->c_str());
           Logger::logDebug("Subscribed to \"" + *it + "\"\n");
        }
     }
     else
     {
        Logger::logDebug("failed!\n");
     }
   }

  return (mqttClient.connected());
}

bool MqttAdapter::parseTopic(
   const String& topic,
   String& componentId,
   String& messageId)
{
   const String SEPERATORS = "/";
   const int MAX_NUM_TOKENS = 5;
   const int MIN_NUM_TOKENS = 3;

   bool parsed = false;

   String tokens[MAX_NUM_TOKENS] = {"", "", "", "", ""};
   String remainingString = topic;

   int i = 0;
   tokens[i] = Utility::tokenize(remainingString, SEPERATORS);

   while (remainingString.length() > 0)
   {
      String token =  Utility::tokenize(remainingString, SEPERATORS);

      i++;
      if (i < MAX_NUM_TOKENS)
      {
         tokens[i] = token;
      }
   }

   int tokenCount = (i + 1);

   // Our expected format: companyname.com/.../component/message
   if (tokenCount >= MIN_NUM_TOKENS)
   {
      componentId = tokens[tokenCount - 2];
      messageId = tokens[tokenCount - 1];
      parsed = true;
   }
   else
   {
      Logger::logDebug("Not enough tokens.\n");
   }

   return (parsed);
}
