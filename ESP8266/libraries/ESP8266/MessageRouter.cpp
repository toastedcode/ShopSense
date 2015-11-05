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
#include "Logger.h"
#include "MessageRouter.h"

MessageRouter* MessageRouter::instance = 0;

void MessageRouter::run()
{
   for (int i = 0; i < MAX_NUM_ADAPTERS; i++)
   {
      if (adapters[i] != 0)
      {
         handleMessages(*adapters[i]);
      }
   }
}

bool MessageRouter::sendMessage(
   const Message& message)
{
   bool sentMessage = false;

   // Retrieve the adapter.
   Adapter* adapter = getAdapter(message.getDestination());

   if (adapter == 0)
   {
      Logger::logDebug("Failed to send " + message.getMessageId() +
                       ". No adapter specified for destination \"" + message.getDestination() + "\"\n");
   }
   else
   {
      // Send the message over the adapter.
      sentMessage = adapter->sendMessage(message);
   }
}

bool MessageRouter::registerAdapter(
   Adapter& adapter)
{
   bool isRegistered = false;

   // Find an empty slot and store the adapter.
   for (int i = 0; i < MAX_NUM_ADAPTERS; i++)
   {
      if (adapters[i] == 0)
      {
         adapters[i] = &adapter;
         isRegistered = true;
         break;
      }
   }

   // Log a failure to register.
   if (isRegistered == false)
   {
      Logger::logDebug("Failed to register adapter " + adapter.getId() + ".\n");
   }

   return (isRegistered);
}

bool MessageRouter::registerHandler(
   MessageHandler& handler)
{
   bool isRegistered = false;

   // Find an empty slot and store the handler.
   for (int i = 0; i < MAX_NUM_HANDLERS; i++)
   {
      if (handlers[i] == 0)
      {
         handlers[i] = &handler;
         isRegistered = true;
         break;
      }
   }

   // Log a failure to register.
   if (isRegistered == false)
   {
      Logger::logDebug("Failed to register handler " + handler.getId() + ".\n");
   }

   return (isRegistered);
}

MessageRouter::MessageRouter()
{
   // Initialize our array of registered adapters.
   for (int i = 0; i < MAX_NUM_ADAPTERS; i++)
   {
      adapters[i] = 0;
   }

   // Initialize our array of registered handlers.
   for (int i = 0; i < MAX_NUM_HANDLERS; i++)
   {
      handlers[i] = 0;
   }
}

MessageRouter::~MessageRouter()
{

}

Adapter* MessageRouter::getAdapter(
   const String& adapterId)
{
   Adapter* adapter = 0;

   for (int i = 0; i < MAX_NUM_ADAPTERS; i++)
   {
      if ((adapters[i] != 0) &&
          (adapters[i]->getId() == adapterId))
      {
         adapter = adapters[i];
         break;
      }
   }

   return (adapter);
}

MessageHandler* MessageRouter::getHandler(
   const String& handlerId)
{
   MessageHandler* handler = 0;

   for (int i = 0; i < MAX_NUM_HANDLERS; i++)
   {
      if ((handlers[i] != 0) &&
          (handlers[i]->getId() == handlerId))
      {
         handler = handlers[i];
         break;
      }
   }

   return (handler);
}

void MessageRouter::handleMessages(
   Adapter& adapter)
{
   bool handledMessage = false;

   // Get the first available message.
   const Message* message = adapter.getMessage();

   while (message != 0)
   {
      MessageHandler* handler = getHandler(message->getDestination());

      if (handler == 0)
      {
         Logger::logDebug("Failed to handle message " + message->getMessageId() +
                          ". No handler specified for destination \"" + message->getDestination() + "\"\n");
      }
      else
      {
         // Send the message over the adapter.
         handledMessage = handler->handleMessage(*message);
      }

      // Free up the memory from the handled message.
      delete message;

      // Get the next available message.
      message = adapter.getMessage();
   }
}
