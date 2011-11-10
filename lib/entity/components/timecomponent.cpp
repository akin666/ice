/*
 * timecomponent.cpp
 *
 *  Created on: 31.10.2011
 *      Author: akin
 */

#include "timecomponent.h"
#include <entity/properties/timeproperty.h>
#include <entity/storage>
#include <sys/time.h>

namespace ice
{

TimeComponent::TimeComponent() throw (ComponentException)
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

void TimeComponent::attach( Entity& entity ) throw (ComponentException)
{
	property->attach( entity );

	entities.push_back( entity.id );
}

void TimeComponent::detach( Entity& entity ) throw (ComponentException)
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

void TimeComponent::start() throw (ComponentException)
{
	if( !initialized )
	{
		now = clock.getCurrentTime();
		property->setCurrentTime( now );
		initialized = true;
	}


	last = now;
	now = clock.getCurrentTime();
	diff = now - last;

	property->setCurrentTime( now );

	schedule( work );
}

} /* namespace ice */


