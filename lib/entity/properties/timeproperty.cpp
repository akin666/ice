/*
 * timeproperty.cpp
 *
 *  Created on: 1.11.2011
 *      Author: akin
 */

#include "timeproperty.h"
#include <entity/entity>

namespace ice
{
const std::string TimeProperty::KEY("time");

TimeProperty::TimeProperty()
: Property( KEY )
{
}

TimeProperty::~TimeProperty()
{
}

void TimeProperty::attach( Entity& entity )
{
	TimeType::iterator iter = timeData.find( entity.id );
	if( iter != timeData.end() )
	{
		return;
	}

	timeData[ entity.id ];
}

void TimeProperty::detach( Entity& entity )
{
	timeData.erase( entity.id );
}

Time& TimeProperty::get( EntityKey key )
{
	return timeData[ key ];
}

std::map< unsigned int , Time >& TimeProperty::getTime()
{
	return timeData;
}

void TimeProperty::setCurrentTime( Time time )
{
	last = current;
	current = time;

	diff = current - last;
}

Time TimeProperty::getDiff()
{
	return diff;
}

Time TimeProperty::getNow()
{
	return current;
}

Time TimeProperty::getPrevious()
{
	return last;
}

} /* namespace ice */
