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
#include <deque>
#include "../component"
#include <entity/properties/timeproperty.h>
#include <entity/properties/forceproperty.h>
#include <entity/properties/positionproperty.h>
#include <entity/properties/weightproperty.h>

namespace ice
{

class BulletPhysicsComponent : public Component
{
protected:

	class BPData {
	public:
		btCollisionShape* shape;
		btDefaultMotionState* motionState;
		btRigidBody* body;

		BPData()
		: shape( NULL ),
		  motionState( NULL ),
		  body( NULL )
		{
		}

		BPData( const BPData& other )
		: shape( other.shape ),
		  motionState( other.motionState ),
		  body( other.body )
		{
		}
	};

	///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
	btDefaultCollisionConfiguration* collisionConfiguration;

	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	btCollisionDispatcher* dispatcher;

	///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
	btBroadphaseInterface* overlappingPairCache;

	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	btSequentialImpulseConstraintSolver* solver;

	// world
	btDiscreteDynamicsWorld* dynamicsWorld;

	// Plane
	BPData ground;

	// Shapes
	btAlignedObjectArray<btCollisionShape*> collisionShapes;

	std::deque<EntityKey> entities;

	std::map< EntityKey , BPData > pdata;

	TimeProperty *timeProperty;
	PositionProperty *positionProperty;
	WeightProperty *weightProperty;
public:
	BulletPhysicsComponent() throw (ComponentException);
	virtual ~BulletPhysicsComponent();

	virtual void attach( Entity& entity ) throw (ComponentException);
	virtual void detach( Entity& entity ) throw (ComponentException);

	virtual void start() throw (ComponentException);
};

} /* namespace ice */
#endif /* BULLETPHYSICSCOMPONENT_H_ */
