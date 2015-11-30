// *****************************************************************************
// *****************************************************************************
// ToastBot.h
//
// Author: Jason Tost
// Date:   11.30.2015
//
// *****************************************************************************
// *****************************************************************************

#ifndef TOASTBOT_H_INCLUDED
#define TOASTBOT_H_INCLUDED

#include "MessageHandler.h"
#include "WebServerAdapter.h"

class ToastBot : public MessageHandler
{

public:

   // Get the Singleton instance.
   static ToastBot* getInstance();

   void begin();

   void run();

   // **************************************************************************
   //                         Message handler operations

   // This operation handles a message.
   // True is returned if the message was successfully handled; false otherwise.
   virtual bool handleMessage(
      // The message to handle.
      const Message& message);

   // **************************************************************************

private:

   // Constructor.
   ToastBot();

   // Destructor.
   ~ToastBot();

   // The Singleton instance.
   static ToastBot* instance;

   // Adapters.
   WebServerAdapter adapter;
};

// *****************************************************************************
//                               Inline functions

inline ToastBot* ToastBot::getInstance()
{
   if (instance == 0)
   {
      instance = new ToastBot();
   }

   return (instance);
}

inline ToastBot::ToastBot() : MessageHandler("TOAST_BOT")
{

}

inline ToastBot::~ToastBot()
{
   // Nothing to do here.
}

#endif  // TOASTBOT_H_INCLUDED
