// *****************************************************************************
// *****************************************************************************
// Message.h
//
// Author: Jason Tost
// Date:   10.29.2015
//
// *****************************************************************************
// *****************************************************************************

#ifndef MESSAGE_H_INCLUDED
#define MESSAGE_H_INCLUDED

#include "Arduino.h"

class Message
{

public:

   // Constructor.
   Message(
      const String& messageId);

   // Destructor.
   virtual ~Message();

   // This operation sets the source and destination fields of the message.
   void address(
      // The source of the message.
      const String& sourceId,
      // The destination of the message.
      const String& destinationId);

   // This operation retrieves the message id.
   String getMessageId() const;

   // This operation retrieves the message id.
   String getSource() const;

   // This operation retrieves the message id.
   String getDestination() const;

   // A unique identifier for a server adapter.
   static const String SERVER_ID;

private:

   // The message id associated with this message.
   String messageId;

   // The source of the message.
   String sourceId;

   // The destination of the message.
   String destinationId;

};

// *****************************************************************************
//                               Inline functions

inline String Message::getMessageId() const
{
   return (messageId);
}

inline String Message::getSource() const
{
   return (sourceId);
}

inline String Message::getDestination() const
{
   return (destinationId);
}

#endif  // MESSAGE_H_INCLUDED
