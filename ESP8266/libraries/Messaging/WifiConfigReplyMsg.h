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
   static String getMessageId();

private:

};

// *****************************************************************************
//                               Inline functions

inline WifiConfigReplyMsg::WifiConfigReplyMsg() : Message(getMessageId())
{
}

inline WifiConfigReplyMsg::~WifiConfigReplyMsg()
{
}

inline String WifiConfigReplyMsg::getMessageId()
{
   return ("WIFI_CONFIG_REPLY_MSG");
}

#endif  // WIFICONFIGREPLYMSG_H_INCLUDED
