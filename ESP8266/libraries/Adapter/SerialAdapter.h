// *****************************************************************************
// *****************************************************************************
// SerialAdapter.h
//
// Author: Jason Tost
// Date:   11.23.2015
//
// *****************************************************************************
// *****************************************************************************

#ifndef SERIALADAPTER_H_INCLUDED
#define SERIALADAPTER_H_INCLUDED

#include "Adapter.h"

class SerialAdapter : public Adapter
{

public:

   // Constructor.
   SerialAdapter(
      // A unique identifier for the adapter.
      // Note: This is the id that should be used in the "to" field of messages that are to be sent out this adapter.
      const String& id);

   // Destructor.
   virtual ~SerialAdapter();


   void setup();

   // This operation sends the specified message.
   virtual bool sendMessage(
      // The message that is to be sent.
      const Message& message);

   // This operation retrieves the next available message.
   // Returns a null pointer if no messages are available.
   virtual const Message* getMessage();

protected:

};

// *****************************************************************************
//                               Inline functions

inline void SerialAdapter::setup()
{
}

#endif  // SERIALADAPTER_H_INCLUDED
