// *****************************************************************************
// *****************************************************************************
// WebAdapter.h
//
// Author: Jason Tost
// Date:   11.2.2015
//
// *****************************************************************************
// *****************************************************************************

#ifndef WEBCONTROLADAPTER_H_INCLUDED
#define WEBCONTROLADAPTER_H_INCLUDED

#include "Adapter.h"
#include "ESP8266WiFi.h"

class WebControlAdapter : public Adapter
{

public:

   // Constructor.
   WebControlAdapter(
      // A unique identifier for the adapter.
      // Note: This is the id that should be used in the "to" field of messages that are to be sent out this adapter.
      const String& id);

   // Destructor.
   virtual ~WebControlAdapter();

   void setup();

   // This operation sends the specified message.
   virtual bool sendMessage(
      // The message that is to be sent.
      const Message& message);

   // This operation retrieves the next available message.
   // Returns a null pointer if no messages are available.
   virtual const Message* getMessage();

protected:

   // A reuable server object for receiving HTTP messages.
   static WiFiServer server;

   // A reusable client object for sending HTTP messages.
   static WiFiClient client;

private:

   // This operation extracts the destination component from an incoming message.
   static String getDestination(
      // The message string to parse.
      const String& string);
};

// *****************************************************************************
//                               Inline functions

#endif  // WEBCONTROLADAPTER_H_INCLUDED
