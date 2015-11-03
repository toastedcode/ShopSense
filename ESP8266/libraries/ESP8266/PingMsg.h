// *****************************************************************************
// *****************************************************************************
// SensorUpdateMsg.h
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
   static String getMessageId();

private:

};

// *****************************************************************************
//                               Inline functions

inline PingMsg::PingMsg() : Message(getMessageId())
{
}

inline PingMsg::~PingMsg()
{
}

inline String PingMsg::getMessageId()
{
   return ("PING_MSG");
}

#endif  // PINGMSG_H_INCLUDED
