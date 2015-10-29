// *****************************************************************************
// *****************************************************************************
// MessageRouter.h
//
// Author: Jason Tost
// Date:   10.27.2015
//
// *****************************************************************************
// *****************************************************************************

#ifndef HTTPPROTOCOL_H_INCLUDED
#define HTTPPROTOCOL_H_INCLUDED

#include "Arduino.h"
#include "Message.h"
#include "Protocol.h"

class HttpProtocol : public Protocol
{

public:

   HttpProtocol();

   virtual ~HttpProtocol();

   virtual bool parse(
      const String& string,
      Message* message);

   virtual bool serialize(
      const Message* message,
      String& serializedMessage);

private:

};

#endif  // HTTPPROTOCOL_H_INCLUDED
