// *****************************************************************************
// *****************************************************************************
// Adapter.cpp
//
// Author: Jason Tost
// Date:   11.2.2015
//
// *****************************************************************************
// *****************************************************************************

#include "Adapter.h"

Adapter::Adapter(
   const String& id)
{
   this->id = id;
   protocol = 0;
}

Adapter::~Adapter()
{
}
