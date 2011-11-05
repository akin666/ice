/*
 * DIOLocker.cpp
 *
 *  Created on: 6.3.2011
 *      Author: akin
 */

#include "diolocker.h"
#include "dataio.h"

namespace ice
{
	DIOLocker::DIOLocker( DIO &dio )
	{
		ptr = &dio;
		ptr->lock();
	}

	DIOLocker::~DIOLocker()
	{
		ptr->unlock();
	}
}

