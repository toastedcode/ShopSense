// *****************************************************************************
// *****************************************************************************
// VibrationSensorConfigMsg.h
//
// Author: Jason Tost
// Date:   12.2.2015
//
// *****************************************************************************
// *****************************************************************************

#ifndef VIBRATIONSENSORCONFIGREPLYMSG_H_INCLUDED
#define VIBRATIONSENSORCONFIGREPLYMSG_H_INCLUDED

#include "VibrationSensorConfigMsg.h"

class VibrationSensorConfigReplyMsg : public VibrationSensorConfigMsg
{

public:

   // Constructor.
   VibrationSensorConfigReplyMsg(
      // The sensor id.
      const String& sensorId,
      // The server IP address.
      const String& serverIpAddress,
      // The configured sensor sensitivity.
      const int& sensitivity,
      // The configured sensor responsiveness.
      const int& responsiveness,
      // A flag indicating if the sensor is enabled.
      const bool& isEnabled,
      // A flag indicating if the sensor was successfully configured.
      const bool& success);

   // Destructor.
   virtual ~VibrationSensorConfigReplyMsg();

   // This operation returns the unique message id.
   virtual MessageId getMessageId() const;

   // This operation returns a flag indicating if the sensor was successfully configured.
   bool getSuccess() const;

   // Unique message id.
   static const MessageId MESSAGE_ID = VIBRATION_SENSOR_CONFIG_REPLY;

private:

   // A flag indicating if the sensor was successfully configured.
   bool success;
};

// *****************************************************************************
//                               Inline functions

inline VibrationSensorConfigReplyMsg::VibrationSensorConfigReplyMsg(
   const String& sensorId,
   const String& serverIpAddress,
   const int& sensitivity,
   const int& responsiveness,
   const bool& isEnabled,
   const bool& success) : VibrationSensorConfigMsg(sensorId, serverIpAddress, sensitivity, responsiveness, isEnabled)
{
   this->success = success;
}

inline VibrationSensorConfigReplyMsg::~VibrationSensorConfigReplyMsg()
{
   // Nothing to do here.
}

inline MessageId VibrationSensorConfigReplyMsg::getMessageId() const
{
   return (MESSAGE_ID);
}

inline bool VibrationSensorConfigReplyMsg::getSuccess() const
{
   return (success);
}

#endif  // VIBRATIONSENSORCONFIGREPLYMSG_H_INCLUDED
