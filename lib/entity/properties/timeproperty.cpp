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

TimeProperty::TimeProperty()
: Property( PROPERTY_TIME_NAME )
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

} /* namespace ice */
