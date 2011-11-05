/*
 * timework.cpp
 *
 *  Created on: 1.11.2011
 *      Author: akin
 */

#include "timework.h"
#include "timecomponent.h"

namespace ice
{

TimeWork::TimeWork( CCComponent& parent )
: ComponentWork( parent )
{
}

TimeWork::~TimeWork()
{
}

bool TimeWork::begin()
{
	// nothing is holding back.
	return true;
}

void TimeWork::run()
{
	TimeComponent *tcparent = dynamic_cast<TimeComponent*>( &parent );

	if( tcparent == NULL || tcparent->property == NULL )
	{
		return;
	}

	TimeProperty *property = tcparent->property;
	std::deque<EntityKey>& entities = tcparent->entities;
	Time diff = tcparent->diff;

	// How much time has happened to each component.
	// Set the time to each component!
	for( std::deque<EntityKey>::iterator iter = entities.begin() ; iter != entities.end() ; ++iter )
	{
		property->get( *iter ) = diff;
	}
}

} /* namespace ice */
