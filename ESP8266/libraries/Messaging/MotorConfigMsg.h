// *****************************************************************************
// *****************************************************************************
// MotorConfigMsg.h
//
// Author: Jason Tost
// Date:   12.10.2015
//
// *****************************************************************************
// *****************************************************************************

#ifndef MOTORCONFIGMSG_H_INCLUDED
#define MOTORCONFIGMSG_H_INCLUDED

#include "Message.h"

class MotorConfigMsg : public Message
{

public:

   // Constructor.
   MotorConfigMsg(
      // The value that is to be written.
      const int& speed);

   // Destructor.
   virtual ~MotorConfigMsg();

   // This operation returns the unique message id.
   virtual MessageId getMessageId() const;

   // This operation returns the motor speed.
   int getSpeed() const;

   // Unique message id.
   static const MessageId MESSAGE_ID = MOTOR_CONFIG;

private:

   // The motor speed.
   int speed;
};

// *****************************************************************************
//                               Inline functions

inline MotorConfigMsg::MotorConfigMsg(
   const int& speed) : Message()
{
   this->speed = speed;
}

inline MotorConfigMsg::~MotorConfigMsg()
{
}

inline MessageId MotorConfigMsg::getMessageId() const
{
   return (MESSAGE_ID);
}

inline int MotorConfigMsg::getSpeed() const
{
   return (speed);
}

#endif  // MOTORCONFIGMSG_H_INCLUDED
