// *****************************************************************************
// *****************************************************************************
// SetLoggingMsg.h
//
// Author: Jason Tost
// Date:   11.23.2015
//
// *****************************************************************************
// *****************************************************************************

#ifndef SETLOGGINGMSG_H_INCLUDED
#define SETLOGGINGMSG_H_INCLUDED

#include "Message.h"

class SetLoggingMsg : public Message
{

public:

   // Constructor.
   SetLoggingMsg(
      // A flag indicating if logging should be enabled.
      const bool& loggingEnabled);

   // Destructor.
   virtual ~SetLoggingMsg();

   // This operation returns the unique message id.
   virtual MessageId getMessageId() const;

   // This operation returns true if logging is to be enabled.
   bool isLoggingEnabled() const;

   // Unique message id.
   static const MessageId MESSAGE_ID = SET_LOGGING;

private:

   // A flag indicating if logging should be enabled.
   bool loggingEnabled;
};

// *****************************************************************************
//                               Inline functions

inline SetLoggingMsg::SetLoggingMsg(
   const bool& loggingEnabled) : Message()
{
   this->loggingEnabled = loggingEnabled;
}

inline SetLoggingMsg::~SetLoggingMsg()
{
}

inline MessageId SetLoggingMsg::getMessageId() const
{
   return (MESSAGE_ID);
}

inline bool SetLoggingMsg::isLoggingEnabled() const
{
   return (loggingEnabled);
}

#endif  // SETLOGGINGMSG_H_INCLUDED
