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
      const String& sensorId,
      const int& sensorReading);

   // Destructor.
   virtual ~SensorUpdateMsg();

   // This operation returns the unique message id.
   static String getMessageId();

   // This operation returns the id of the sensor being reported.
   String getSensorId() const;

   // This operation returns the sensor reading being reported.
   int getSensorReading() const;

private:

   // The id of the sensor being reported.
   String sensorId;

   // The sensor reading being reported.
   int sensorReading;

};

// *****************************************************************************
//                               Inline functions

inline String SensorUpdateMsg::getMessageId()
{
   return ("SENSOR_UPDATE_MSG");
}

inline String SensorUpdateMsg::getSensorId() const
{
   return (sensorId);
}

inline int SensorUpdateMsg::getSensorReading() const
{
   return (sensorReading);
}

#endif  // SENSORUPDATEMSG_H_INCLUDED
