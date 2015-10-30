// *****************************************************************************
// *****************************************************************************
// MessageRouter.cpp
//
// Author: Jason Tost
// Date:   10.27.2015
//
// *****************************************************************************
// *****************************************************************************

#include "ESP8266WiFi.h"
#include "HttpProtocol.h"
#include "Logger.h"
#include "MessageRouter.h"

const String MessageRouter::SERVER_ID = "server";

bool MessageRouter::sendMessage(
   const Message* message)
{
   HttpProtocol protocol;
   String serializedMessage;

   if (protocol.serialize(message, serializedMessage) == true)
   {
      // TODO: Implement using adapters.
      serializedMessage = "GET /shopSense.php?" + serializedMessage + " HTTP/1.0";

      WiFiClient client;

      // Connect to the server.
      if (client.connect("www.roboxes.com", 80) == false)
      {
         Logger::logDebug("Failed to connect to server.\n");
      }
      else
      {
         Logger::logDebug("Sending: " + serializedMessage + "\n");

         // Make the request.
         client.println(serializedMessage);
         client.println("HOST: roboxes.com");
         client.println();

         // Read all the lines of the reply from server.
         while(client.available())
         {
            String line = client.readStringUntil('\r');
            Logger::logDebug(line);
         }
      }
   }
   else
   {
      Logger::logDebug("Failed to serialize message " + message->getMessageId() + ".\n");
   }
}
