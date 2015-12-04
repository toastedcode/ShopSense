// *****************************************************************************
// *****************************************************************************
// PingReplyMsg.h
//
// Author: Jason Tost
// Date:   11.21.2015
//
// *****************************************************************************
// *****************************************************************************

#ifndef PINGREPLYMSG_H_INCLUDED
#define PINGREPLYMSG_H_INCLUDED

#include "Message.h"

class PingReplyMsg : public Message
{

public:

   // Constructor.
   PingReplyMsg(
      const String& ipAddress);

   // Destructor.
   virtual ~PingReplyMsg();

   // This operation returns the unique message id.
   virtual MessageId getMessageId() const;

   // This operation retrieves the IP address of the reply.
   String getIpAddress() const;

   // Unique message id.
   static const MessageId MESSAGE_ID = PING_REPLY;

private:

   // The IP address of the reply.
   String ipAddress;
};

// *****************************************************************************
//                               Inline functions

inline PingReplyMsg::PingReplyMsg(
   const String& ipAddress) : Message()
{
   this->ipAddress = ipAddress;
}

inline PingReplyMsg::~PingReplyMsg()
{
}

inline MessageId PingReplyMsg::getMessageId() const
{
   return (MESSAGE_ID);
}

inline String PingReplyMsg::getIpAddress() const
{
   return (ipAddress);
}

#endif  // PINGREPLYMSG_H_INCLUDED
