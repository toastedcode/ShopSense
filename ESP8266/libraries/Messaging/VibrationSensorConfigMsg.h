// *****************************************************************************
// *****************************************************************************
// VibrationSensorConfigMsg.h
//
// Author: Jason Tost
// Date:   12.2.2015
//
// *****************************************************************************
// *****************************************************************************

#ifndef VIBRATIONSENSORCONFIGMSG_H_INCLUDED
#define VIBRATIONSENSORCONFIGMSG_H_INCLUDED

#include "Message.h"

class VibrationSensorConfigMsg : public Message
{

public:

   // Constructor.
   VibrationSensorConfigMsg(
      // The sensor id.
      const String& sensorId,
      // The server IP address.
      const String& serverIpAddress,
      // The configured sensor sensitivity.
      const int& sensitivity,
      // The configured sensor responsiveness.
      const int& responsiveness,
      // A flag indicating if the sensor is enabled.
      const bool& isEnabled);

   // Destructor.
   virtual ~VibrationSensorConfigMsg();

   // This operation retrieves the message id.
   virtual MessageId getMessageId() const;

   // This operation returns the sensor id.
   String getSensorId() const;

   // This operation returns the server IP address.
   String getServerIpAddress() const;

   // This operation returns the sensor sentivity.
   int getSensitivity() const;

   // This operation returns the sensor responsiveness.
   int getResponsiveness() const;

   // This operation returns a flag indicating if the sensor is enabled.
   bool getIsEnabled() const;

   // Unique message id.
   static const MessageId MESSAGE_ID = VIBRATION_SENSOR_CONFIG;

private:

   // The sensor id.
   String sensorId;

   // The server IP address.
   String serverIpAddress;

   // The sensor sensitivity.
   int sensitivity;

   // The sensor responsiveness.
   int responsiveness;

   // A flag indicating if the sensor is enabled.
   bool isEnabled;
};

// *****************************************************************************
//                               Inline functions

inline VibrationSensorConfigMsg::VibrationSensorConfigMsg(
   const String& sensorId,
   const String& serverIpAddress,
   const int& sensitivity,
   const int& responsiveness,
   const bool& isEnabled) : Message()
{
   this->sensorId = sensorId;
   this->serverIpAddress = serverIpAddress;
   this->sensitivity = sensitivity;
   this->responsiveness = responsiveness;
   this->isEnabled = isEnabled;
}

inline VibrationSensorConfigMsg::~VibrationSensorConfigMsg()
{
   // Nothing to do here.
}

inline MessageId VibrationSensorConfigMsg::getMessageId() const
{
   return (MESSAGE_ID);
}

inline String VibrationSensorConfigMsg::getSensorId() const
{
   return (sensorId);
}

inline String VibrationSensorConfigMsg::getServerIpAddress() const
{
   return (serverIpAddress);
}

inline int VibrationSensorConfigMsg::getSensitivity() const
{
   return (sensitivity);
}

inline int VibrationSensorConfigMsg::getResponsiveness() const
{
   return (responsiveness);
}

inline bool VibrationSensorConfigMsg::getIsEnabled() const
{
   return (isEnabled);
}

#endif  // VIBRATIONSENSORCONFIGMSG_H_INCLUDED
