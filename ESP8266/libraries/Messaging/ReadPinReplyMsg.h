// *****************************************************************************
// *****************************************************************************
// ReadPinReplyMsg.h
//
// Author: Jason Tost
// Date:   11.23.2015
//
// *****************************************************************************
// *****************************************************************************

#ifndef READPINREPLYMSG_H_INCLUDED
#define READPINREPLYMSG_H_INCLUDED

#include "Message.h"

class ReadPinReplyMsg : public Message
{

public:

   // Constructor.
   ReadPinReplyMsg(
      // The pin that was to be read.
      const int& pinId,
      // The value read from the pin.
      const int& value,
      // A flag indicating if the pin was successfully read.
      const bool& success);

   // Destructor.
   virtual ~ReadPinReplyMsg();

   // This operation returns the unique message id.
   static String getMessageId();

   // This operation returns the pin that is to be read.
   int getPin() const;

   // This operation returns the value read from the pin.
   int getValue() const;

   // This operation returns a flag indicating if the pin was successfully read.
   bool getSuccess() const;

private:

   // The pin that was to be read.
   int pinId;

   // The value read from the pin.
   int value;

   // A flag indicating if the pin was successfully read.
   bool success;
};

// *****************************************************************************
//                               Inline functions

inline ReadPinReplyMsg::ReadPinReplyMsg(
   const int& pinId,
   const int& value,
   const bool& success) : Message(getMessageId())
{
   this->pinId = pinId;
   this->value = value;
   this->success = success;
}

inline ReadPinReplyMsg::~ReadPinReplyMsg()
{
}

inline String ReadPinReplyMsg::getMessageId()
{
   return ("READ_PIN_REPLY_MSG");
}

inline int ReadPinReplyMsg::getPin() const
{
   return (pinId);
}

inline int ReadPinReplyMsg::getValue() const
{
   return (value);
}

inline bool ReadPinReplyMsg::getSuccess() const
{
   return (success);
}

#endif  // READPINREPLYMSG_H_INCLUDED
