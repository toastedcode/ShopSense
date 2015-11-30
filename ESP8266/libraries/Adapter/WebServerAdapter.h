// *****************************************************************************
// *****************************************************************************
// WebServerAdapter.h
//
// Author: Jason Tost
// Date:   11.30.2015
//
// *****************************************************************************
// *****************************************************************************

#ifndef WEBSERVERADAPTER_H_INCLUDED
#define WEBSERVERADAPTER_H_INCLUDED

#include "Adapter.h"
#include "ESP8266WiFi.h"

class WebServerAdapter : public Adapter
{

public:

   // Constructor.
   WebServerAdapter();

   // Destructor.
   virtual ~WebServerAdapter();

   // Starts the web server.
   void begin();

   // **************************************************************************
   //                           Adapter operations.

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

#endif  // WEBSERVERADAPTER_H_INCLUDED
