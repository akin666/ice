/*
 * boundingsphereproperty.cpp
 *
 *  Created on: 4.11.2011
 *      Author: akin
 */

#include "boundingsphereproperty.h"

namespace ice
{
const std::string BoundingSphereProperty::KEY("boundingsphere");

BoundingSphereProperty::BoundingSphereProperty()
: Property( KEY )
{
}

BoundingSphereProperty::~BoundingSphereProperty()
{
}

void BoundingSphereProperty::attach( Entity& entity )
{
	SphereType::iterator iter = spheres.find( entity.id );
	if( iter != spheres.end() )
	{
		return;
	}

	spheres[ entity.id ];
}

void BoundingSphereProperty::detach( Entity& entity )
{
	spheres.erase( entity.id );
}

// Property specific methods.
float& BoundingSphereProperty::get( EntityKey entity )
{
	return spheres[ entity ];
}

} /* namespace ice */
