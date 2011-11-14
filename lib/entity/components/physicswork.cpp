/*
 * physicswork.cpp
 *
 *  Created on: 1.11.2011
 *      Author: akin
 */

#include "physicswork.h"
#include "physicscomponent.h"
#include <iostream>

namespace ice
{

PhysicsWork::PhysicsWork( Component& parent )
: ComponentWork( parent )
{
}

PhysicsWork::~PhysicsWork()
{
}

bool PhysicsWork::begin()
{
	// nothing is holding back.
	return true;
}

void PhysicsWork::run()
{
	// Do Blody Physics..
	PhysicsComponent *tcparent = dynamic_cast<PhysicsComponent*>( &parent );

	if( tcparent == NULL ||
		tcparent->timeProperty == NULL ||
		tcparent->forceProperty == NULL ||
		tcparent->positionProperty == NULL  ||
		tcparent->weightProperty == NULL )
	{
		return;
	}

	TimeProperty *timeProperty = tcparent->timeProperty;
	ForceProperty *forceProperty = tcparent->forceProperty;
	PositionProperty *positionProperty = tcparent->positionProperty;
	WeightProperty *weightProperty = tcparent->weightProperty;

	std::deque<EntityKey>& entities = tcparent->entities;

	Time step = timeProperty->getDiff();

	if( step == 0 )
	{
		return;
	}

	float seconds = step * 0.001f;

	float gravity = tcparent->gravity;
	float drag = tcparent->drag;

	// Do physics!
	float gravityEffect;
	for( int i = entities.size() - 1 ; i >= 0 ; --i )
	{
		// Get data references..
		EntityKey entity = entities.at( i );
		//Time& time = timeProperty->get( entity );
		float& weight = weightProperty->get( entity );
		ForceProperty::Data& forceData = forceProperty->get( entity );
		PositionProperty::Data& positionData = positionProperty->get( entity );

		//seconds = time * 0.001f; // convert ms to s.

		// Now using time, weight, forces, and position.. update position and other datas.
		forceData.position.y -= gravity * weight * seconds;

		// flip
		if( positionData.position.y < 0.0f && forceData.position.y < 0 )
		{
			forceData.position.y = -forceData.position.y;
		}

		// Add forces to positions.
		positionData.position += forceData.position * seconds;

			std::cout << "------------------" << std::endl;
			std::cout << "gravity:" << gravity << " seconds:" << seconds << " weight:" << weight << std::endl;
			std::cout << "FORCES to X:" << forceData.position.x << " Y:" << forceData.position.y << " Z:" << forceData.position.z << std::endl;
			std::cout << "ID:" << entity << "\tUpdated to X:" << positionData.position.x << " Y:" << positionData.position.y << " Z:" << positionData.position.z << std::endl;
	}
}

} /* namespace ice */
