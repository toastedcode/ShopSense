// *****************************************************************************
// *****************************************************************************
// MessageRouter.h
//
// Author: Jason Tost
// Date:   10.27.2015
//
// *****************************************************************************
// *****************************************************************************

#ifndef PROTOCOL_H_INCLUDED
#define PROTOCOL_H_INCLUDED

#include "Arduino.h"
#include "Message.h"

class Protocol
{

public:

   Protocol();

   virtual ~Protocol();

   virtual bool parse(
      const String& string,
      Message* message) = 0;

   virtual bool serialize(
      const Message* message,
      String& serializedMessage) = 0;

private:

};

#endif  // PROTOCOL_H_INCLUDED
