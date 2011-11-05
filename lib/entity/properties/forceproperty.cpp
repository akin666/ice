/*
 * forceproperty.cpp
 *
 *  Created on: 1.11.2011
 *      Author: akin
 */

#include "forceproperty.h"

namespace ice
{

ForceProperty::ForceProperty()
: Property( PROPERTY_FORCE_NAME )
{
}

ForceProperty::~ForceProperty()
{
}

void ForceProperty::attach( Entity& entity )
{
	ForceType::iterator iter = forces.find( entity.id );
	if( iter != forces.end() )
	{
		return;
	}

	forces[ entity.id ];
}

void ForceProperty::detach( Entity& entity )
{
	forces.erase( entity.id );
}

// Property specific methods.
ForceProperty::Data& ForceProperty::get( EntityKey entity )
{
	return forces[ entity ];
}

} /* namespace ice */
