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
      // The server IP address.
      const String& serverIpAddress,
      // The configured sensor sensitivity.
      const int& sensitivity,
      // The configured sensor responsiveness.
      const int& responsiveness,
      // The sensor update rate.
      const int& updateRate,
      // A flag indicating if the sensor is enabled.
      const bool& isEnabled);

   // Destructor.
   virtual ~VibrationSensorConfigMsg();

   // This operation returns the unique message id.
   static String getMessageId();

   // This operation returns the server IP address.
   String getServerIpAddress() const;

   // This operation returns the sensor sentivity.
   int getSensitivity() const;

   // This operation returns the sensor responsiveness.
   int getResponsiveness() const;

   // This operation returns the sensor update rate.
   int getUpdateRate() const;

   // This operation returns a flag indicating if the sensor is enabled.
   bool getIsEnabled() const;

private:

   // The server IP address.
   String serverIpAddress;

   // The sensor sensitivity.
   int sensitivity;

   // The sensor responsiveness.
   int responsiveness;

   // The senor update rate.
   int updateRate;

   // A flag indicating if the sensor is enabled.
   bool isEnabled;
};

// *****************************************************************************
//                               Inline functions

inline VibrationSensorConfigMsg::VibrationSensorConfigMsg(
   const String& serverIpAddress,
   const int& sensitivity,
   const int& responsiveness,
   const int& updateRate,
   const bool& isEnabled) : Message(getMessageId())
{
   this->serverIpAddress = serverIpAddress;
   this->sensitivity = sensitivity;
   this->responsiveness = responsiveness;
   this->updateRate = updateRate;
   this->isEnabled = isEnabled;
}

inline VibrationSensorConfigMsg::~VibrationSensorConfigMsg()
{
   // Nothing to do here.
}

inline String VibrationSensorConfigMsg::getMessageId()
{
   return ("VIBRATION_SENSOR_CONFIG_MSG");
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

inline int VibrationSensorConfigMsg::getUpdateRate() const
{
   return (updateRate);
}

inline bool VibrationSensorConfigMsg::getIsEnabled() const
{
   return (isEnabled);
}

#endif  // VIBRATIONSENSORCONFIGMSG_H_INCLUDED
