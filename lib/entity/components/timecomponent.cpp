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
const std::string TimeComponent::KEY("time");

TimeComponent::TimeComponent() throw (ComponentException)
: Component( KEY , true ),
  work( *this )
{
	// Initialize properties also, if needed.
	property = Storage::createProperty<TimeProperty>();
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
	property->setCurrentTime( clock.getCurrentTime() );

	schedule( work );
}

} /* namespace ice */


