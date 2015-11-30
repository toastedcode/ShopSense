// *****************************************************************************
// *****************************************************************************
// WritePinReplyMsg.h
//
// Author: Jason Tost
// Date:   11.23.2015
//
// *****************************************************************************
// *****************************************************************************

#ifndef WRITEPINREPLYMSG_H_INCLUDED
#define WRITEPINREPLYMSG_H_INCLUDED

#include "Message.h"

class WritePinReplyMsg : public Message
{

public:

   // Constructor.
   WritePinReplyMsg(
      // The pin that was to be written.
      const int& pinId,
      // The value that was to be written.
      const int& value,
      // A flag indicating if the pin was successfully written.
      const bool& success);

   // Destructor.
   virtual ~WritePinReplyMsg();

   // This operation returns the unique message id.
   static String getMessageId();

   // This operation returns the pin that was to be written.
   int getPin() const;

   // This operation returns the pin that was to be written.
   int getValue() const;

   // This operation returns a flag indicating if the pin was successfully written.
   bool getSuccess() const;

private:

   // The pin that was to be read.
   int pinId;

   // The value that is to be written.
   int value;

   // A flag indicating if the pin was successfully read.
   bool success;
};

// *****************************************************************************
//                               Inline functions

inline WritePinReplyMsg::WritePinReplyMsg(
   const int& pinId,
   const int& value,
   const bool& success) : Message(getMessageId())
{
   this->pinId = pinId;
   this->value = value;
   this->success = success;
}

inline WritePinReplyMsg::~WritePinReplyMsg()
{
}

inline String WritePinReplyMsg::getMessageId()
{
   return ("WRITE_PIN_REPLY_MSG");
}

inline int WritePinReplyMsg::getPin() const
{
   return (pinId);
}

inline int WritePinReplyMsg::getValue() const
{
   return (value);
}

inline bool WritePinReplyMsg::getSuccess() const
{
   return (success);
}

#endif  // WRITEPINREPLYMSG_H_INCLUDED
