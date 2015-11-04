// *****************************************************************************
// *****************************************************************************
// Message.cpp
//
// Author: Jason Tost
// Date:   10.29.2015
//
// *****************************************************************************
// *****************************************************************************

#include "Message.h"

Message::Message(
   const String& messageId)
{
   this->messageId = messageId;
}

Message::~Message()
{
   // Nothing to do here.
}

void Message::address(
   const String& sourceId,
   const String& destinationId)
{
   this->sourceId = sourceId;
   this->destinationId = destinationId;
}
