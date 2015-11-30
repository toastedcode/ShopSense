// *****************************************************************************
// *****************************************************************************
// WifiConfig.h
//
// Author: Jason Tost
// Date:   11.23.2015
//
// *****************************************************************************
// *****************************************************************************

#ifndef WIFICONFIGMSG_H_INCLUDED
#define WIFICONFIGMSG_H_INCLUDED

#include "Message.h"

class WifiConfigMsg : public Message
{

public:

   // Constructor.
   WifiConfigMsg(
      // The wifi SSID.
      const String& ssid,
      // The wifi password.
      const String& password);

   // Destructor.
   virtual ~WifiConfigMsg();

   // This operation returns the unique message id.
   static String getMessageId();

   // This operation returns the wifi SSID.
   String getSsid() const;

   // This operation returns the wifi password.
   String getPassword() const;

private:

   // The wifi SSID.
   String ssid;

   // The wifi password.
   String password;
};

// *****************************************************************************
//                               Inline functions

inline WifiConfigMsg::WifiConfigMsg(
   const String& ssid,
   const String& password) : Message(getMessageId())
{
   this->ssid = ssid;
   this->password = password;
}

inline WifiConfigMsg::~WifiConfigMsg()
{
}

inline String WifiConfigMsg::getMessageId()
{
   return ("WIFI_CONFIG_MSG");
}

inline String WifiConfigMsg::getSsid() const
{
   return (ssid);
}

inline String WifiConfigMsg::getPassword() const
{
   return (password);
}

#endif  // WIFICONFIGMSG_H_INCLUDED
