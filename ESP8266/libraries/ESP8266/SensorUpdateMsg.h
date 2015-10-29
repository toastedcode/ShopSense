// *****************************************************************************
// *****************************************************************************
// SensorUpdateMsg.h
//
// Author: Jason Tost
// Date:   10.29.2015
//
// *****************************************************************************
// *****************************************************************************

#ifndef SENSORUPDATEMSG_H_INCLUDED
#define SENSORUPDATEMSG_H_INCLUDED

#include "Message.h"

class SensorUpdateMsg : public Message
{

public:

   // Constructor.
   SensorUpdateMsg(
      const String& sourceId,
      const String& destinationId,
      const int& sensorReading);

   // Destructor.
   virtual ~SensorUpdateMsg();

   // This operation returns the unique message id.
   static String getMessageId();

private:

   int sensorReading;

};

// *****************************************************************************
//                               Inline functions

inline String SensorUpdateMsg::getMessageId()
{
   return ("SENSOR_UPDATE_MSG");
}

#endif  // SENSORUPDATEMSG_H_INCLUDED
