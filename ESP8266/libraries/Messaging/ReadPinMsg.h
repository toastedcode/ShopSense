// *****************************************************************************
// *****************************************************************************
// ReadPinMsg.h
//
// Author: Jason Tost
// Date:   11.23.2015
//
// *****************************************************************************
// *****************************************************************************

#ifndef READPINMSG_H_INCLUDED
#define READPINMSG_H_INCLUDED

#include "Message.h"

class ReadPinMsg : public Message
{

public:

   // Constructor.
   ReadPinMsg(
      // The pin that is to be read.
      const int& pinId);

   // Destructor.
   virtual ~ReadPinMsg();

   // This operation returns the unique message id.
   virtual MessageId getMessageId() const;

   // This operation returns the pin that is to be read.
   int getPin() const;

   // Unique message id.
   static const MessageId MESSAGE_ID = READ_PIN;

private:

   // The pin that is to be read.
   int pinId;

};

// *****************************************************************************
//                               Inline functions

inline ReadPinMsg::ReadPinMsg(
   const int& pinId) : Message()
{
   this->pinId = pinId;
}

inline ReadPinMsg::~ReadPinMsg()
{
}

inline MessageId ReadPinMsg::getMessageId() const
{
   return (MESSAGE_ID);
}

inline int ReadPinMsg::getPin() const
{
   return (pinId);
}

#endif  // READPINMSG_H_INCLUDED
