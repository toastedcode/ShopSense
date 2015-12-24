// *****************************************************************************
// *****************************************************************************
// WebClientAdapter.cpp
//
// Author: Jason Tost
// Date:   12.2.2015
//
// *****************************************************************************
// *****************************************************************************

#include "Logger.h"
#include "Utility.h"
#include "WebClientAdapter.h"

// Default HTTP port.
static const int HTTP_PORT = 80;

WiFiClient WebClientAdapter::client;

WebClientAdapter::WebClientAdapter(
   const String& id) : Adapter(id)
{
   serverAddress = "";
   serverPage = "";
}

WebClientAdapter::~WebClientAdapter()
{
}

bool WebClientAdapter::sendMessage(
   const Message& message)
{
   bool messageSent = false;

   String serializedMessage;

   if ((protocol != 0) &&
       (protocol->serialize(message, serializedMessage) == true))
   {
      // Format for HTTP GET request.
      serializedMessage = "GET " + serializedMessage + " HTTP/1.0";

      // Connect to the server.
      if (client.connect(serverAddress.c_str(), HTTP_PORT) == false)
      {
         Logger::logDebug("Failed to connect to server.\n");
      }
      else
      {
         Logger::logDebug("Sending: " + serializedMessage + "\n");

         // Make the request.
         client.println(serializedMessage);
         client.println("HOST: dweet.io");
         client.println();

         messageSent = true;

         // Wait for data.
         while ((client.connected()) &&
                (!client.available()))
         {
            delay(1);
         }

         // Read all the lines of the reply from server.
         // TODO: Turn this into a message.
         while (client.available())
         {
            String line = client.readStringUntil('\r');
            Logger::logDebug(line);
         }

         client.stop();
      }
   }
   else
   {
      Logger::logDebug("Failed to serialize message " + toString(message.getMessageId()) + ".\n");
   }

   return (messageSent);
}

const Message* WebClientAdapter::getMessage()
{
   Message* message = 0;

   // TODO: Give reply message from last request.

   return (message);
}
