// *****************************************************************************
// *****************************************************************************
// Component.h
//
// Author: Jason Tost
// Date:   12.9.2015
//
// *****************************************************************************
// *****************************************************************************

#ifndef COMPONENT_H_INCLUDED
#define COMPONENT_H_INCLUDED

#include "MessageHandler.h"

class Component : public MessageHandler
{

public:

   // Constructor.
   Component(
      // A unique identifer for this component.
      const String& id);

   // Destructor.
   virtual ~Component();

   // This operation should be called on startup to prepare the sensor for polling/updating.
   virtual void setup() = 0;

   // This operation should be called continuously from within the main control loop.
   virtual void run() = 0;

   // This operation handles a message.
   // True is returned if the message was successfully handled; false otherwise.
   virtual bool handleMessage(
      // The message to handle.
      const Message& message) = 0;
};

// *****************************************************************************
//                               Inline functions

inline Component::Component(
   const String& id) : MessageHandler(id)
{
   // Nothing to do here.
}

// Destructor.
inline Component::~Component()
{
   // Nothing to do here.
}

#endif  // COMPONENT_H_INCLUDED


