/*
 * DIOLocker.cpp
 *
 *  Created on: 6.3.2011
 *      Author: akin
 */

#include "diolocker"
#include "dio"

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

