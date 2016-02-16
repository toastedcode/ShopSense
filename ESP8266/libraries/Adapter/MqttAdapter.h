// *****************************************************************************
// *****************************************************************************
// MqttAdapter.h
//
// Author: Jason Tost
// Date:   11.2.2015
//
// *****************************************************************************
// *****************************************************************************

#ifndef MQTTADAPTER_H_INCLUDED
#define MQTTADAPTER_H_INCLUDED

#include "Adapter.h"
#include "ESP8266WiFi.h"
#include "PubSubClient.h"
#include "QueueList.h"
#include "SimpleList.h"

class MqttAdapter : public Adapter, PubSubClient::SubscriptionHandler
{

public:

   // Constructor.
   MqttAdapter(
      // A unique identifier for the adapter.
      // Note: This is the id that should be used in the "to" field of messages that are to be sent out this adapter.
      const String& id);

   // Destructor.
   virtual ~MqttAdapter();

   // This operation sets the server address.
   void setServerAddress(
      const String& serverAddress,
      const unsigned int& port);

   // This operation sets the publish topic.
   void setPublishTopic(
      const String& publishTopic);

   // This operation sends the specified message.
   virtual bool sendMessage(
      // The message that is to be sent.
      const Message& message);

   // This operation retrieves the next available message.
   // Returns a null pointer if no messages are available.
   virtual const Message* getMessage();

   // This operation subscribes to the specified topic.
   void subscribe(
      // The topic to subscribe.
      const String& topic);

   void callback(
      char* topic,
      unsigned char* payload,
      unsigned int length);

private:

   bool connect();

   static bool parseTopic(
      const String& topic,
      String& componentId,
      String& messageId);

   // A client object for sending/receiving IP messages.
   static WiFiClient client;

   // A MQTT client object for connecting to a MQTT broker.
   static PubSubClient mqttClient;

   // The address of the MQTT server.
   String serverAddress;

   // The port used in connecting to the MQTT server.
   unsigned int port;

   // The topic used in MQTT publish commands.
   String publishTopic;

   // Queue for incoming messages.
   QueueList<Message*> messageQueue;

   // Subscription list.
   SimpleList<String> subscriptions;
};

// *****************************************************************************
//                               Inline functions

inline void MqttAdapter::setServerAddress(
   const String& serverAddress,
   const unsigned int& port)
{
   this->serverAddress = serverAddress;
   this->port = port;
}

inline void MqttAdapter::setPublishTopic(
   const String& publishTopic)
{
   this->publishTopic = publishTopic;
}

#endif  // MQTTADAPTER_H_INCLUDED
