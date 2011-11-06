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

PhysicsComponent::PhysicsComponent() throw (ComponentException)
: CCComponent( COMPONENT_PHYSICS_NAME ),
  work( *this ),
  gravity( 0.0981f ), // gravity affecting a gram per second.
  drag( 1.0f )
{
	addDependency( COMPONENT_TIME_NAME );

	timeProperty = Storage::createProperty<TimeProperty>( PROPERTY_TIME_NAME );
	forceProperty = Storage::createProperty<ForceProperty>( PROPERTY_FORCE_NAME );
	positionProperty = Storage::createProperty<PositionProperty>( PROPERTY_POSITION_NAME );
	weightProperty = Storage::createProperty<WeightProperty>( PROPERTY_WEIGHT_NAME );
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
