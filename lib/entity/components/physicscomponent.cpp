/*
 * physicscomponent.cpp
 *
 *  Created on: 1.11.2011
 *      Author: akin
 */

#include "physicscomponent.h"
#include <entity/storage>
#include "timecomponent.h"

namespace ice
{
const std::string PhysicsComponent::KEY("physics");

PhysicsComponent::PhysicsComponent() throw (ComponentException)
: CCComponent( KEY ),
  work( *this ),
  gravity( 0.0981f ), // gravity affecting a gram per second.
  drag( 1.0f )
{
	addDependency( TimeComponent::KEY );

	timeProperty = Storage::createProperty<TimeProperty>();
	forceProperty = Storage::createProperty<ForceProperty>();
	positionProperty = Storage::createProperty<PositionProperty>();
	weightProperty = Storage::createProperty<WeightProperty>();
}

PhysicsComponent::~PhysicsComponent()
{
}

void PhysicsComponent::attach( Entity& entity ) throw (ComponentException)
{
	timeProperty->attach( entity );
	forceProperty->attach( entity );
	positionProperty->attach( entity );
	weightProperty->attach( entity );

	entities.push_back( entity.id );
}

void PhysicsComponent::detach( Entity& entity ) throw (ComponentException)
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

void PhysicsComponent::start() throw (ComponentException)
{
	// Run physics to the specified components.
	// using time etc. that they got.
	schedule( work );
}

} /* namespace ice */
