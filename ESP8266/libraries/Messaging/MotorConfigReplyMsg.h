// *****************************************************************************
// *****************************************************************************
// MotorConfigReplyMsg.h
//
// Author: Jason Tost
// Date:   12.10.2015
//
// *****************************************************************************
// *****************************************************************************

#ifndef MOTORCONFIGREPLYMSG_H_INCLUDED
#define MOTORCONFIGREPLYMSG_H_INCLUDED

#include "MotorConfigMsg.h"

class MotorConfigReplyMsg : public MotorConfigMsg
{

public:

   // Constructor.
   MotorConfigReplyMsg(
      // The value that is to be written.
      const int& speed);

   // Destructor.
   virtual ~MotorConfigReplyMsg();

   // This operation returns the unique message id.
   virtual MessageId getMessageId() const;

   // Unique message id.
   static const MessageId MESSAGE_ID = MOTOR_CONFIG_REPLY;

private:

};

// *****************************************************************************
//                               Inline functions

inline MotorConfigReplyMsg::MotorConfigReplyMsg(
   const int& speed) : MotorConfigMsg(speed)
{
   // Nothing to do here.
}

inline MotorConfigReplyMsg::~MotorConfigReplyMsg()
{
   // Nothing to do here.
}

inline MessageId MotorConfigReplyMsg::getMessageId() const
{
   return (MESSAGE_ID);
}

#endif  // MOTORCONFIGREPLYMSG_H_INCLUDED
