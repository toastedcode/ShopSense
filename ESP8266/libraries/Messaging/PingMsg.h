// *****************************************************************************
// *****************************************************************************
// PingMsg.h
//
// Author: Jason Tost
// Date:   10.29.2015
//
// *****************************************************************************
// *****************************************************************************

#ifndef PINGMSG_H_INCLUDED
#define PINGMSG_H_INCLUDED

#include "Message.h"

class PingMsg : public Message
{

public:

   // Constructor.
   PingMsg();

   // Destructor.
   virtual ~PingMsg();

   // This operation returns the unique message id.
   virtual MessageId getMessageId() const;

   static const MessageId MESSAGE_ID = PING;

private:

};

// *****************************************************************************
//                               Inline functions

inline PingMsg::PingMsg() : Message()
{
}

inline PingMsg::~PingMsg()
{
}

inline MessageId PingMsg::getMessageId() const
{
   return (MESSAGE_ID);
}

#endif  // PINGMSG_H_INCLUDED
