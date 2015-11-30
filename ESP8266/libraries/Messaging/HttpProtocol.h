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

   // Constructor.
   HttpProtocol();

   // Destructor.
   virtual ~HttpProtocol();

   virtual bool parse(
      const String& string,
      Message*& message);

   virtual bool serialize(
      const Message& message,
      String& serializedMessage);

private:

   // This operation parses out the specified parameter from a string.
   bool getParameter(
      // The string to parse.
      const String& string,
      // The parameter name to search for.
      const String& parameterName,
      // A flag indicating if the parameter should be optional.
      const bool& isOptional,
      // The parsed parameter.
      String& parameter) const;

   // This operation adds standard HTTP headers to the supplied content to form a complete HTTP reply.
   static String httpReply(
      const String& content);
};

// *****************************************************************************
//                               Inline functions

inline HttpProtocol::HttpProtocol()
{
}

inline HttpProtocol::~HttpProtocol()
{
}

#endif  // HTTPPROTOCOL_H_INCLUDED
