// *****************************************************************************
// *****************************************************************************
// WebServerAdapter.cpp
//
// Author: Jason Tost
// Date:   11.30.2015
//
// *****************************************************************************
// *****************************************************************************

#include "Logger.h"
#include "HttpProtocol.h"
#include "Utility.h"
#include "WebServerAdapter.h"

// Default HTTP port.
static const int HTTP_PORT = 80;

WiFiClient WebServerAdapter::client;

WiFiServer WebServerAdapter::server(HTTP_PORT);

WebServerAdapter::WebServerAdapter() : Adapter("WEB_SERVER")
{
   protocol = new HttpProtocol();
}

WebServerAdapter::~WebServerAdapter()
{
   delete protocol;
}

void WebServerAdapter::begin()
{
   server.begin();
}

bool WebServerAdapter::sendMessage(
   const Message& message)
{
   bool messageSent = false;

   String serializedMessage;

   if (client && client.connected())
   {
      if ((protocol) &&
          (protocol->serialize(message, serializedMessage) == true))
      {
         Logger::logDebug("Sending: " + serializedMessage + "\n");
         client.print(serializedMessage);
      }
      else
      {
         Logger::logDebug("Failed to serialize message " + toString(message.getMessageId()) + ".\n");
      }
   }
   else
   {
      Logger::logDebug("Failed to send message. Client at " + Utility::toString(client.remoteIP()) + " disconnected.");
   }

   client.stop();

   return (messageSent);
}

const Message* WebServerAdapter::getMessage()
{
   Message* message = 0;

   client = server.available();

   if (client)
   {
      Logger::logDebug("Client connected from " + Utility::toString(client.remoteIP()) + "\n");

      // Wait for data.
      while ((client.connected()) &&
             (!client.available()))
      {
         delay(1);
      }

      if (client.available())
      {
         String string = client.readStringUntil('\r');
         client.flush();

         protocol->parse(string, message);

         if (message)
         {
            message->address(getId(), message->getDestination());
         }
      }
   }

   return (message);
}

// TODO: Use protocol to extract destination from raw message.
String WebServerAdapter::getDestination(
   const String& string)
{
   return ("");
}
