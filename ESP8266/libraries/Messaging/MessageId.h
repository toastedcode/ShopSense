// *****************************************************************************
// *****************************************************************************
// MessageId.h
//
// Author: Jason Tost
// Date:   12.4.2015
//
// *****************************************************************************
// *****************************************************************************

#ifndef MESSAGEID_H_INCLUDED
#define MESSAGEID_H_INCLUDED

enum MessageId
{
   PING,
   PING_REPLY,
   READ_PIN,
   READ_PIN_REPLY,
   WRITE_PIN,
   WRITE_PIN_REPLY,
   WIFI_CONFIG,
   WIFI_CONFIG_REPLY,
   VIBRATION_SENSOR_CONFIG,
   VIBRATION_SENSOR_CONFIG_REPLY,
   SENSOR_UPDATE,
   SET_UPDATE_RATE,
   MOTOR_CONFIG,
   MOTOR_CONFIG_REPLY,
   SET_LOGGING,
};

const String MESSAGE_ID_STRINGS[]
{
   "PING",
   "PING_REPLY",
   "READ_PIN",
   "READ_PIN_REPLY",
   "WRITE_PIN",
   "WRITE_PIN_REPLY",
   "WIFI_CONFIG",
   "WIFI_CONFIG_REPLY",
   "VIBRATION_SENSOR_CONFIG",
   "VIBRATION_SENSOR_CONFIG_REPLY",
   "SENSOR_UPDATE",
   "SET_UPDATE_RATE",
   "MOTOR_CONFIG",
   "MOTOR_CONFIG_REPLY",
   "SET_LOGGING"
};

inline String toString(
   const MessageId& messageId)
{
   return (MESSAGE_ID_STRINGS[messageId]);
}

#endif
