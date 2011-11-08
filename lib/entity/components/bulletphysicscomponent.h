/*
 * bulletphysicscomponent.h
 *
 *  Created on: 8.11.2011
 *      Author: akin
 */

#ifndef BULLETPHYSICSCOMPONENT_H_
#define BULLETPHYSICSCOMPONENT_H_

#include <btBulletDynamicsCommon.h>
#include <map>

namespace ice
{

class BulletPhysicsComponent : public CCComponent
{
protected:
	// World
	btDynamicsWorld* m_dynamicsWorld;



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
	BulletPhysicsComponent() throw (ComponentException);
	virtual ~BulletPhysicsComponent();

	virtual void attach( Entity& entity ) throw (ComponentException);
	virtual void detach( Entity& entity ) throw (ComponentException);

	virtual void start() throw (ComponentException);
};

} /* namespace ice */
#endif /* BULLETPHYSICSCOMPONENT_H_ */
