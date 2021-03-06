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
      const int& sensorReading,
      const int& sensorReadingTime);

   // Constructor.
   SensorUpdateMsg(
      const String& sensorId,
      const int& sensorReading);

   // Destructor.
   virtual ~SensorUpdateMsg();

   // This operation returns the unique message id.
   virtual MessageId getMessageId() const;

   // This operation returns the id of the sensor being reported.
   String getSensorId() const;

   // This operation returns the sensor reading being reported.
   int getSensorReading() const;

   // This operation returns the sensor reading time being reported.
   int getSensorReadingTime() const;

   // Unique message id.
   static const MessageId MESSAGE_ID = SENSOR_UPDATE;

private:

   // The id of the sensor being reported.
   String sensorId;

   // The sensor reading being reported.
   int sensorReading;

   // The time that the sensor has been in the reported state.
   int sensorReadingTime;

};

// *****************************************************************************
//                               Inline functions

inline SensorUpdateMsg::SensorUpdateMsg(
   const String& sensorId,
   const int& sensorReading,
   const int& sensorReadingTime) : Message()
{
   this->sensorId = sensorId;
   this->sensorReading = sensorReading;
   this->sensorReadingTime = sensorReadingTime;
}

inline SensorUpdateMsg::SensorUpdateMsg(
   const String& sensorId,
   const int& sensorReading) : SensorUpdateMsg(sensorId, sensorReading, 0)
{
   // Nothing to do here.
}

inline SensorUpdateMsg::~SensorUpdateMsg()
{
}

inline MessageId SensorUpdateMsg::getMessageId() const
{
   return (MESSAGE_ID);
}

inline String SensorUpdateMsg::getSensorId() const
{
   return (sensorId);
}

inline int SensorUpdateMsg::getSensorReading() const
{
   return (sensorReading);
}

inline int SensorUpdateMsg::getSensorReadingTime() const
{
   return (sensorReadingTime);
}

#endif  // SENSORUPDATEMSG_H_INCLUDED
