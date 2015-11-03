// *****************************************************************************
// *****************************************************************************
// Adapter.h
//
// Author: Jason Tost
// Date:   11.2.2015
//
// *****************************************************************************
// *****************************************************************************

#ifndef ADAPTER_H_INCLUDED
#define ADAPTER_H_INCLUDED

#include "Message.h"
#include "Protocol.h"

class Adapter
{

public:

   // Constructor.
   Adapter(
      // A unique identifier for the adapter.
      // Note: This is the id that should be used in the "to" field of messages that are to be sent out this adapter.
      const String& id);

   // Destructor.
   virtual ~Adapter();

   // This operation retrieves the unique id for the adapter.
   String getId();

   // This operation sets the protocol object that will be used for serializing/parsing messages.
   void setProtocol(
      // The protocol to use.
      Protocol& protocol);

   // This operation sends the specified message.
   virtual bool sendMessage(
      // The message that is to be sent.
      const Message& message) = 0;

   // This operation retrieves the next available message.
   // Returns a null pointer if no messages are available.
   virtual const Message* getMessage() = 0;

protected:

   // A unique identifier for the adapter.
   // Note: This is the id that should be used in the "to" field of messages that are to be sent out this adapter.
   String id;

   // The protocol object that will be sued for serializing/parsing messages.
   Protocol* protocol;

};

// *****************************************************************************
//                               Inline functions

inline String Adapter::getId()
{
   return (id);
}

inline void Adapter::setProtocol(
   Protocol& protocol)
{
   this->protocol = &protocol;
}

#endif  // ADAPTER_H_INCLUDED
