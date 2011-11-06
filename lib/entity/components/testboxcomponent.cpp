/*
 * testboxcomponent.cpp
 *
 *  Created on: 3.11.2011
 *      Author: akin
 */

#include "testboxcomponent.h"
#include "physicscomponent.h"
#include <entity/storage>
#include <system/opengl>

namespace ice
{

TestBoxComponent::TestBoxComponent() throw (ComponentException)
: Component( COMPONENT_TESTBOX_NAME )
{
	addDependency( COMPONENT_PHYSICS_NAME );

	positionProperty = Storage::createProperty<PositionProperty>( PROPERTY_POSITION_NAME );
}

TestBoxComponent::~TestBoxComponent()
{
}

void TestBoxComponent::attach( Entity& entity ) throw (ComponentException)
{
	positionProperty->attach( entity );

	entities.push_back( entity.id );
}

void TestBoxComponent::detach( Entity& entity ) throw (ComponentException)
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

void TestBoxComponent::start() throw (ComponentException)
{
	glColor3f( 1.0f , 1.0f , 1.0f );
	// Draw a box at entity location.
	for( std::deque<EntityKey>::iterator iter = entities.begin() ; iter != entities.end() ; ++iter )
	{
		PositionProperty::Data& position = positionProperty->get( *iter );

		// Render at point
		glBegin( GL_POINTS );
		glVertex3f( position.position.x , position.position.y , position.position.z );
		glEnd();
	}

	finish();
}

} /* namespace ice */
