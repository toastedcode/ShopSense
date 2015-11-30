// *****************************************************************************
// *****************************************************************************
// MessageRouter.h
//
// Author: Jason Tost
// Date:   10.27.2015
//
// *****************************************************************************
// *****************************************************************************

#ifndef MESSAGEROUTER_H_INCLUDED
#define MESSAGEROUTER_H_INCLUDED

#include "Adapter.h"
#include "Arduino.h"
#include "Message.h"
#include "MessageHandler.h"

class MessageRouter
{

public:

   // Get the Singleton instance.
   static MessageRouter* getInstance();

   void begin();

   // This operation should be called continuously from within the main control loop.
   // Allows for reading of messages from all registered adapters.
   void run();

   // This operation sends the specified message.
   // Note: The adapter to use for sending should be specified in the "to" field.
   bool sendMessage(
      // The message to send.
      const Message& message);

   // This operation registers an adapter for sending/receiving messages.
   // True is returned if the adapter was successfully registered; false otherwise.
   bool registerAdapter(
      // The adapter that is to be registered.
      Adapter& adapter);

   // This operation registers a message handler for receiving messages.
   // True is returned if the handler was successfully registered; false otherwise.
   bool registerHandler(
      // The message handler that is to be registered.
      MessageHandler& handler,
      // A flag indicating if this handler should be used as the default message handler.
      const bool& isDefaultHandler = false);

private:

   // Constructor.
   MessageRouter();

   // Destructor.
   virtual ~MessageRouter();

   // This operation retrieves the adapter that was registered with the specified id.
   // Null is returned if no adapter was registered using the specified id.
   Adapter* getAdapter(
      // The id of the registered adapter.
      const String& adapterId);

   // This operation retrieves the adapter that was registered with the specified id.
   // Null is returned if no handler was registered using the specified id.
   MessageHandler* getHandler(
      // The id of the registered handler.
      const String& handlerId);

   // This operation handles any available messages on the specified adapter.
   void handleMessages(
      // The adapter to use in handling messages.
      Adapter& adapter);

   // The Singleton instance.
   static MessageRouter* instance;

   // A constant specifying the maximum number of adapters supported by the Message Router.
   static const int MAX_NUM_ADAPTERS = 5;

   // A constant specifying the maximum number of message handlers supported by the Message Router.
   static const int MAX_NUM_HANDLERS = 5;

   // An array of registered adapters.
   Adapter* adapters[MAX_NUM_ADAPTERS];

   // An array of registered adapters.
   MessageHandler* handlers[MAX_NUM_HANDLERS];

   // The message handler that will be used when no destination is supplied.
   MessageHandler* defaultHandler;
};

// *****************************************************************************
//                               Inline functions

inline MessageRouter* MessageRouter::getInstance()
{
   if (instance == 0)
   {
      instance = new MessageRouter();
   }

   return (instance);
}

#endif  // MESSAGEROUTER_H_INCLUDED
