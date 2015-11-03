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
#include "WebAdapter.h"

// Default HTTP port.
static const int HTTP_PORT = 80;

WiFiClient WebAdapter::client;

WiFiServer WebAdapter::server(HTTP_PORT);

WebAdapter::WebAdapter(
   const String& id) : Adapter(id)
{
   serverAddress = "";
   serverPage = "";

   server.begin();
}

WebAdapter::~WebAdapter()
{
}

bool WebAdapter::sendMessage(
   const Message& message)
{
   bool messageSent = false;

   String serializedMessage;

   if ((protocol != 0) &&
       (protocol->serialize(message, serializedMessage) == true))
   {
      // Format for HTTP GET request.
      serializedMessage = "GET /shopSense.php?" + serializedMessage + " HTTP/1.0";

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
         client.println("HOST: roboxes.com");
         client.println();

         messageSent = true;

         // Read all the lines of the reply from server.
         // TODO: Turn this into a message.
         while (client.available())
         {
            String line = client.readStringUntil('\r');
            Logger::logDebug(line);
         }

         //client.disconnect();
      }
   }
   else
   {
      Logger::logDebug("Failed to serialize message " + message.getMessageId() + ".\n");
   }

   return (messageSent);
}

const Message* WebAdapter::getMessage()
{
   Message* message = 0;

   WiFiClient connectedClient = server.available();

   if (connectedClient.available())
   {
      String string = connectedClient.readStringUntil('\r');
      connectedClient.flush();

      protocol->parse(string, message);
   }

   return (message);
}

/*
    PRINTDEBUG("new client");
    whileTimeout = millis();
    while (!clientS.available() ) {
      if (  (millis() - whileTimeout) > WHILE_TO ) {
        clientS.stop();
        return;
      }
      delay(1);
    }
    String req = clientS.readStringUntil('\r');
    PRINTDEBUG(req);
    clientS.flush();
    int val = 1;
    if (req.indexOf("/gpio/0") != -1) // LOW
      dude.changeState(LOW);
    else if (req.indexOf("/gpio/1") != -1) //HIGH
      dude.changeState(HIGH);
    else if  (req.indexOf("/gpio/s") != -1) {} // GET STATUS
    else if  (req.indexOf("/gpio/u") != -1) {
      val = 0;  // UPDATE
*/
