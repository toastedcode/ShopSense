// *****************************************************************************
// *****************************************************************************
// MessageRouter.h
//
// Author: Jason Tost
// Date:   10.27.2015
//
// *****************************************************************************
// *****************************************************************************

#ifndef MESSAGEROUTER_H_INCLUDED
#define MESSAGEROUTER_H_INCLUDED

#include "Arduino.h"
#include "Message.h"

class MessageRouter
{

public:

   static bool sendMessage(
      const Message* message);

   static const String SERVER_ID;

private:

   // Constructor.
   MessageRouter();

   // Destructor.
   virtual ~MessageRouter();
};

// *****************************************************************************
//                               Inline functions

#endif  // MESSAGEROUTER_H_INCLUDED
