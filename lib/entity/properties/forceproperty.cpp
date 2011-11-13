/*
 * forceproperty.cpp
 *
 *  Created on: 1.11.2011
 *      Author: akin
 */

#include "forceproperty.h"

namespace ice
{
const std::string ForceProperty::KEY("force");

ForceProperty::ForceProperty()
: Property( KEY )
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
