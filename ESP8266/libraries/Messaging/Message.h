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
#include "MessageId.h"

// A unique identifier for the ESP8266 object.
const String ESP8266_ID = "esp8266";

// A unique identifier for a server adapter.
const String SERVER_ID = "server";

class Message
{

public:

   // Constructor.
   Message();

   // Destructor.
   virtual ~Message();

   // This operation sets the source and destination fields of the message.
   void address(
      // The source of the message.
      const String& sourceId,
      // The destination of the message.
      const String& destinationId);

   // This operation retrieves the message id.
   virtual MessageId getMessageId() const = 0;

   // This operation retrieves the message id.
   String getSource() const;

   // This operation retrieves the message id.
   String getDestination() const;

private:

   // The source of the message.
   String sourceId;

   // The destination of the message.
   String destinationId;

};

// *****************************************************************************
//                               Inline functions

inline String Message::getSource() const
{
   return (sourceId);
}

inline String Message::getDestination() const
{
   return (destinationId);
}

#endif  // MESSAGE_H_INCLUDED
