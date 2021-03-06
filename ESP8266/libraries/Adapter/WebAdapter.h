// *****************************************************************************
// *****************************************************************************
// WebAdapter.h
//
// Author: Jason Tost
// Date:   11.2.2015
//
// *****************************************************************************
// *****************************************************************************

#ifndef WEBADAPTER_H_INCLUDED
#define WEBADAPTER_H_INCLUDED

#include "Adapter.h"
#include "ESP8266WiFi.h"

class WebAdapter : public Adapter
{

public:

   // Constructor.
   WebAdapter(
      // A unique identifier for the adapter.
      // Note: This is the id that should be used in the "to" field of messages that are to be sent out this adapter.
      const String& id);

   // Destructor.
   virtual ~WebAdapter();

   // This operation sets the server address.
   void setServerAddress(
      const String& serverAddress);

   // This operation sets the server address.
   void setServerPage(
      const String& serverPage);

   // This operation sends the specified message.
   virtual bool sendMessage(
      // The message that is to be sent.
      const Message& message);

   // This operation retrieves the next available message.
   // Returns a null pointer if no messages are available.
   virtual const Message* getMessage();

protected:

   // A reusable client object for sending HTTP messages.
   static WiFiClient client;

   // A reuable server object for receiving HTTP messages.
   static WiFiServer server;

   // The address of the web server used for sending messages.
   String serverAddress;

   // The address of the web paged used for sending messages.
   String serverPage;

};

// *****************************************************************************
//                               Inline functions

inline void WebAdapter::setServerAddress(
   const String& serverAddress)
{
   this->serverAddress = serverAddress;
}

inline void WebAdapter::setServerPage(
   const String& serverPage)
{
   this->serverPage = serverPage;
}

#endif  // WEBADAPTER_H_INCLUDED
