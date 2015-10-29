// *****************************************************************************
// *****************************************************************************
// MessageRouter.cpp
//
// Author: Jason Tost
// Date:   10.27.2015
//
// *****************************************************************************
// *****************************************************************************

#include "HttpProtocol.h"
#include "MessageRouter.h"

const String MessageRouter::SERVER_ID = "server";

bool MessageRouter::sendMessage(
   const Message* message)
{
   HttpProtocol protocol;
   String serializedMessage;

   if (protocol.serialize(message, serializedMessage) == true)
   {

   }
}
