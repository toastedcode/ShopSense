// *****************************************************************************
// *****************************************************************************
// JsonProtocol.h
//
// Author: Jason Tost
// Date:   2.15.2016
//
// *****************************************************************************
// *****************************************************************************

#ifndef JSONPROTOCOL_H_INCLUDED
#define JSONPROTOCOL_H_INCLUDED

#include "Arduino.h"
#include "ArduinoJson.h"
#include "Message.h"
#include "Protocol.h"

class JsonProtocol : public Protocol
{

public:

   // Constructor.
   JsonProtocol();

   // Destructor.
   virtual ~JsonProtocol();

   virtual bool parse(
      const String& string,
      Message*& message);

   virtual bool serialize(
      const Message& message,
      String& serializedMessage);

private:

   // Memory pool for JSON object tree.
   static StaticJsonBuffer<200> jsonBuffer;
};

// *****************************************************************************
//                               Inline functions

inline JsonProtocol::JsonProtocol()
{
}

inline JsonProtocol::~JsonProtocol()
{
}

#endif  // JSONPROTOCOL_H_INCLUDED
