// *****************************************************************************
// *****************************************************************************
// DweetProtocol.h
//
// Author: Jason Tost
// Date:   12.23.2015
//
// *****************************************************************************
// *****************************************************************************

#ifndef DWEETPROTOCOL_H_INCLUDED
#define DWEETPROTOCOL_H_INCLUDED

#include "Arduino.h"
#include "Message.h"
#include "Protocol.h"

class DweetProtocol : public Protocol
{

public:

   // Constructor.
   DweetProtocol();

   // Destructor.
   virtual ~DweetProtocol();

   virtual bool parse(
      const String& string,
      Message*& message);

   virtual bool serialize(
      const Message& message,
      String& serializedMessage);

private:

};

// *****************************************************************************
//                               Inline functions

inline DweetProtocol::DweetProtocol()
{
}

inline DweetProtocol::~DweetProtocol()
{
}

#endif  // DWEETPROTOCOL_H_INCLUDED
