// *****************************************************************************
// *****************************************************************************
// WritePinMsg.h
//
// Author: Jason Tost
// Date:   11.23.2015
//
// *****************************************************************************
// *****************************************************************************

#ifndef WRITEPINMSG_H_INCLUDED
#define WRITEPINMSG_H_INCLUDED

#include "Message.h"

class WritePinMsg : public Message
{

public:

   // Constructor.
   WritePinMsg(
      // The pin that is to be written.
      const int& pinId,
      // The value that is to be written.
      const int& value);

   // Destructor.
   virtual ~WritePinMsg();

   // This operation returns the unique message id.
   virtual MessageId getMessageId() const;

   // This operation returns the pin that is to be written.
   int getPin() const;

   // This operation returns the value that is to be written.
   int getValue() const;

   // Unique message id.
   static const MessageId MESSAGE_ID = WRITE_PIN;

private:

   // The pin that is to be written.
   int pinId;

   // The value that is to be written.
   int value;

};

// *****************************************************************************
//                               Inline functions

inline WritePinMsg::WritePinMsg(
   const int& pinId,
   const int& value) : Message()
{
   this->pinId = pinId;
   this->value = value;
}

inline WritePinMsg::~WritePinMsg()
{
}

inline MessageId WritePinMsg::getMessageId() const
{
   return (MESSAGE_ID);
}

inline int WritePinMsg::getPin() const
{
   return (pinId);
}

inline int WritePinMsg::getValue() const
{
   return (value);
}

#endif  // WRITEPINMSG_H_INCLUDED
