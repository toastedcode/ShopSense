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
   static String getMessageId();

   // This operation retrieves the IP address of the reply.
   String getIpAddress() const;

private:

   // The IP address of the reply.
   String ipAddress;
};

// *****************************************************************************
//                               Inline functions

inline PingReplyMsg::PingReplyMsg(
   const String& ipAddress) : Message(getMessageId())
{
   this->ipAddress = ipAddress;
}

inline PingReplyMsg::~PingReplyMsg()
{
}

inline String PingReplyMsg::getMessageId()
{
   return ("PING_REPLY");
}

inline String PingReplyMsg::getIpAddress() const
{
   return (ipAddress);
}

#endif  // PINGREPLYMSG_H_INCLUDED
