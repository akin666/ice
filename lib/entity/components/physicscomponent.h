/*
 * physicscomponent.h
 *
 *  Created on: 1.11.2011
 *      Author: akin
 */

#ifndef PHYSICSCOMPONENT_H_
#define PHYSICSCOMPONENT_H_

#include <entity/cccomponent>
#include <entity/entity>
#include <deque>
#include "physicswork.h"
#include <entity/properties/timeproperty.h>
#include <entity/properties/forceproperty.h>
#include <entity/properties/positionproperty.h>
#include <entity/properties/weightproperty.h>

#define COMPONENT_PHYSICS_NAME "physics"

namespace ice
{

class PhysicsComponent : public CCComponent
{
protected:
	std::deque<EntityKey> entities;

	TimeProperty *timeProperty;
	ForceProperty *forceProperty;
	PositionProperty *positionProperty;
	WeightProperty *weightProperty;

	PhysicsWork work;

	float gravity;
	float drag;

	friend class PhysicsWork;
public:
	PhysicsComponent();
	virtual ~PhysicsComponent();

	virtual void attach( Entity& entity );
	virtual void detach( Entity& entity );

	virtual void start();
};

} /* namespace ice */
#endif /* PHYSICSCOMPONENT_H_ */
