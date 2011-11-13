/*
 * bulletphysicscomponent.cpp
 *
 *  Created on: 8.11.2011
 *      Author: akin
 */

#include "bulletphysicscomponent.h"
#include <entity/storage>
#include "timecomponent.h"

namespace ice
{
const std::string BulletPhysicsComponent::KEY("bulletphysics");

BulletPhysicsComponent::BulletPhysicsComponent() throw (ComponentException)
: Component( KEY )
{
	addDependency( TimeComponent::KEY );

	timeProperty = Storage::createProperty<TimeProperty>( TimeProperty::KEY );
	positionProperty = Storage::createProperty<PositionProperty>( PositionProperty::KEY );
	weightProperty = Storage::createProperty<WeightProperty>( PositionProperty::KEY );

	// Init world.
	collisionConfiguration = new btDefaultCollisionConfiguration();

	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	dispatcher = new	btCollisionDispatcher(collisionConfiguration);

	///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
	overlappingPairCache = new btDbvtBroadphase();

	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	solver = new btSequentialImpulseConstraintSolver;

	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,overlappingPairCache,solver,collisionConfiguration);

	dynamicsWorld->setGravity(btVector3(0,-10,0));

	///create a few basic rigid bodies
	ground.shape = new btBoxShape(btVector3(btScalar(50.),btScalar(50.),btScalar(50.)));

	//keep track of the shapes, we release memory at exit.
	//make sure to re-use collision shapes among rigid bodies whenever possible!
	collisionShapes.push_back( ground.shape );

	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(0,-56,0));

	//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
	ground.motionState = new btDefaultMotionState(groundTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(
			btScalar(0.) ,  // Weight
			ground.motionState , //
			ground.shape,	//
			btVector3(0,0,0)// inertia
			);
	ground.body = new btRigidBody(rbInfo);

	//add the body to the dynamics world
	dynamicsWorld->addRigidBody( ground.body );
}

BulletPhysicsComponent::~BulletPhysicsComponent()
{
}

void BulletPhysicsComponent::attach( Entity& entity ) throw (ComponentException)
{
	timeProperty->attach( entity );
	positionProperty->attach( entity );
	weightProperty->attach( entity );

	entities.push_back( entity.id );

	//create a dynamic rigidbody
	{
		BPData tmp;

		float& weight = weightProperty->get( entity.id );
		PositionProperty::Data& position = positionProperty->get(  entity.id  );

		tmp.shape = new btSphereShape(btScalar( weight ));

		collisionShapes.push_back( tmp.shape );

		/// Create Dynamic Objects
		btTransform startTransform;
		startTransform.setIdentity();

		btScalar mass( weight );

		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0,0,0);

		if (isDynamic)
		{
			tmp.shape->calculateLocalInertia(mass,localInertia);
		}

		startTransform.setOrigin(btVector3(position.position.x,position.position.y,position.position.z));

		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		tmp.motionState = new btDefaultMotionState(startTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(
				mass,
				tmp.motionState,
				tmp.shape,
				localInertia
				);

		tmp.body = new btRigidBody(rbInfo);

		dynamicsWorld->addRigidBody( tmp.body );

		pdata[ entity.id ] = tmp;
	}
}

void BulletPhysicsComponent::detach( Entity& entity ) throw (ComponentException)
{
}

void BulletPhysicsComponent::start() throw (ComponentException)
{
	// Do physics tick.
	Time step = timeProperty->getDiff();

	float seconds = step * 0.001f;

	dynamicsWorld->stepSimulation( seconds , 10 );

	// Update dots.
	for( std::map< EntityKey , BPData >::iterator iter = pdata.begin() ; iter != pdata.end() ; ++iter )
	{
		BPData& data = iter->second;
		const EntityKey& key = iter->first;

		PositionProperty::Data& position = positionProperty->get(  key  );

		btTransform trans;

		data.body->getMotionState()->getWorldTransform(trans);

		position.position.x = float(trans.getOrigin().getX());
		position.position.y = float(trans.getOrigin().getY());
		position.position.z = float(trans.getOrigin().getZ());
	}
}

} /* namespace ice */
