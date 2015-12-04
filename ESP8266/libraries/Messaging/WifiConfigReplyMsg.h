// *****************************************************************************
// *****************************************************************************
// WifiConfig.h
//
// Author: Jason Tost
// Date:   11.23.2015
//
// *****************************************************************************
// *****************************************************************************

#ifndef WIFICONFIGREPLYMSG_H_INCLUDED
#define WIFICONFIGREPLYMSG_H_INCLUDED

#include "Message.h"

class WifiConfigReplyMsg : public Message
{

public:

   // Constructor.
   WifiConfigReplyMsg();

   // Destructor.
   virtual ~WifiConfigReplyMsg();

   // This operation returns the unique message id.
   virtual MessageId getMessageId() const;

   // Unique message id.
   static const MessageId MESSAGE_ID = WIFI_CONFIG_REPLY;

private:

};

// *****************************************************************************
//                               Inline functions

inline WifiConfigReplyMsg::WifiConfigReplyMsg() : Message()
{
}

inline WifiConfigReplyMsg::~WifiConfigReplyMsg()
{
}

inline MessageId WifiConfigReplyMsg::getMessageId() const
{
   return (MESSAGE_ID);
}

#endif  // WIFICONFIGREPLYMSG_H_INCLUDED
