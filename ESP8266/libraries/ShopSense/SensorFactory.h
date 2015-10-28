// *****************************************************************************
// *****************************************************************************
// SensorFactory.h
//
// Author: Jason Tost
// Date:   10.27.2015
//
// *****************************************************************************
// *****************************************************************************

#ifndef SENSORFACTORY_H_INCLUDED
#define SENSORFACTORY_H_INCLUDED

class SensorFactory
{
   
   enum SensorType
   {
      GENERIC_ANALOG,
      GENERIC_DIGITAL,
      VIBRATION
   };

   //static Sensor* getSensor(SensorType sensorType);
};

#endif  // SENSORFACTORY_H_INCLUDED
