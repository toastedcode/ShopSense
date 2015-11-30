// *****************************************************************************
// *****************************************************************************
// SetUpdateRateMsg.h
//
// Author: Jason Tost
// Date:   11.3.2015
//
// *****************************************************************************
// *****************************************************************************

#ifndef SETUPDATERATEMSG_H_INCLUDED
#define SETUPDATERATEMSG_H_INCLUDED

#include "Message.h"

class SetUpdateRateMsg : public Message
{

public:

   // Constructor.
   SetUpdateRateMsg(
      const int& updateRate);

   // Destructor.
   virtual ~SetUpdateRateMsg();

   // This operation returns the unique message id.
   static String getMessageId();

   // This operation returns the new update rate for the sensor.
   int getUpdateRate() const;

private:

   // The new update rate for the sensor.
   int updateRate;

};

// *****************************************************************************
//                               Inline functions

inline SetUpdateRateMsg::SetUpdateRateMsg(
   const int& updateRate) : Message(getMessageId())
{
   this->updateRate = updateRate;
}

inline SetUpdateRateMsg::~SetUpdateRateMsg()
{
}

inline String SetUpdateRateMsg::getMessageId()
{
   return ("SET_UPDATE_RATE_MSG");
}

inline int SetUpdateRateMsg::getUpdateRate() const
{
   return (updateRate);
}

#endif  // SETUPDATERATEMSG_H_INCLUDED
