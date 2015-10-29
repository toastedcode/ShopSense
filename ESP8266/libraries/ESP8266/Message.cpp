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
   const String& messageId,
   const String& sourceId,
   const String& destinationId)
{
   this->messageId = messageId;
   this->sourceId = sourceId;
   this->destinationId = destinationId;
}

Message::~Message()
{
   // Nothing to do here.
}
