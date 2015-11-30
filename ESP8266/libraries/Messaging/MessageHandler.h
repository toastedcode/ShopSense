// *****************************************************************************
// *****************************************************************************
// MessageHandler.h
//
// Author: Jason Tost
// Date:   11.3.2015
//
// *****************************************************************************
// *****************************************************************************

#ifndef MESSAGEHANDLER_H_INCLUDED
#define MESSAGEHANDLER_H_INCLUDED

#include "Message.h"

class MessageHandler
{

public:

   // Constructor.
   MessageHandler(
      // A unique identifier for the handler.
      // Note: This is the id that should be used in the "to" field of messages that are to be received by this handler.
      const String& id);

   // Destructor.
   virtual ~MessageHandler();

   // This operation retrieves the unique id for the handler.
   String getId();

   // This operation handles a message.
   // True is returned if the message was successfully handled; false otherwise.
   virtual bool handleMessage(
      // The message to handle.
      const Message& message) = 0;

private:

   // A unique identifier for the handler.
   // Note: This is the id that should be used in the "to" field of messages that are to be received by this handler.
   String id;
};

// *****************************************************************************
//                               Inline functions

inline MessageHandler::MessageHandler(
   const String& id)
{
   this->id = id;
}

inline MessageHandler::~MessageHandler()
{
}

inline String MessageHandler::getId()
{
   return (id);
}


#endif  // MESSAGEHANDLER_H_INCLUDED
