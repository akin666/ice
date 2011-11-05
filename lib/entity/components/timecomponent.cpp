/*
 * timecomponent.cpp
 *
 *  Created on: 31.10.2011
 *      Author: akin
 */

#include "timecomponent.h"
#include <entity/properties/timeproperty.h>
#include <entity/storage>
#include <sys/plattform.h>
#include <sys/time.h>

namespace ice
{

TimeComponent::TimeComponent()
: CCComponent( COMPONENT_TIME_NAME ),
  work( *this ),
  initialized( false )
{
	// Initialize properties also, if needed.
	property = Storage::createProperty<TimeProperty>( PROPERTY_TIME_NAME );
}

TimeComponent::~TimeComponent()
{
}

void TimeComponent::attach( Entity& entity )
{
	property->attach( entity );

	entities.push_back( entity.id );
}

void TimeComponent::detach( Entity& entity )
{
	for( std::deque<EntityKey>::iterator iter = entities.begin() ; iter != entities.end() ; ++iter )
	{
		if( *iter == entity.id )
		{
			entities.erase( iter );
			return;
		}
	}
}

unsigned int getMilliSecTime()
{
	//timezone zone;
	timeval val;

	gettimeofday( &val , NULL );

	return (val.tv_sec * 1000.0) + ( val.tv_usec * 0.001 );
}

void TimeComponent::start()
{
	if( !initialized )
	{
		now = getMilliSecTime();
		initialized = true;
	}


	last = now;
	now = getMilliSecTime();
	diff = now - last;

	schedule( work );
}

} /* namespace ice */


