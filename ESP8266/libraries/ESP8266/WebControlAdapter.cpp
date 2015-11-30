// *****************************************************************************
// *****************************************************************************
// WebAdapter.cpp
//
// Author: Jason Tost
// Date:   11.2.2015
//
// *****************************************************************************
// *****************************************************************************

#include "Logger.h"
#include "Utility.h"
#include "WebControlAdapter.h"

// Default HTTP port.
static const int HTTP_PORT = 80;

WiFiClient WebControlAdapter::client;

WiFiServer WebControlAdapter::server(HTTP_PORT);

WebControlAdapter::WebControlAdapter(
   const String& id) : Adapter(id)
{
   //server.begin();
}

WebControlAdapter::~WebControlAdapter()
{
   // Nothing to do here.
}

void WebControlAdapter::setup()
{
   server.begin();
}

bool WebControlAdapter::sendMessage(
   const Message& message)
{
   bool messageSent = false;

   String serializedMessage;

   if (client && (client.connected()))
   {
      if ((protocol) &&
          (protocol->serialize(message, serializedMessage) == true))
      {
         Logger::logDebug("Sending: " + serializedMessage + "\n");
         client.print(serializedMessage);
      }
      else
      {
         Logger::logDebug("Failed to serialize message " + message.getMessageId() + ".\n");
      }
   }
   else
   {
      Logger::logDebug("Failed to send message. Client at " + Utility::toString(client.remoteIP()) + " disconnected.");
   }

   client.stop();

   return (messageSent);
}

const Message* WebControlAdapter::getMessage()
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

      if (client.connected())
      {
         Logger::logDebug("Client is connected\n");

         if (client.available())
         {
            Logger::logDebug("Data from client is available\n");

            String string = client.readStringUntil('\r');
            client.flush();

            Logger::logDebug("Read data from client: " + string + "\n");

            protocol->parse(string, message);

            if (message)
            {
               message->address(getId(), getDestination(string));
            }
         }
      }
   }

   return (message);
}

String WebControlAdapter::getDestination(
   const String& string)
{
   return ("");
}
