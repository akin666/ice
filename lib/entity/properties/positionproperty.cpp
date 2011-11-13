/*
 * positionproperty.cpp
 *
 *  Created on: 1.11.2011
 *      Author: akin
 */

#include "positionproperty.h"

namespace ice
{
const std::string PositionProperty::KEY("position");

PositionProperty::PositionProperty()
: Property( KEY )
{
}

PositionProperty::~PositionProperty()
{
}

void PositionProperty::attach( Entity& entity )
{
	PositionType::iterator iter = position.find( entity.id );
	if( iter != position.end() )
	{
		return;
	}

	position[ entity.id ];
}

void PositionProperty::detach( Entity& entity )
{
	position.erase( entity.id );
}

// Property specific methods.
PositionProperty::Data& PositionProperty::get( EntityKey entity )
{
	return position[ entity ];
}

} /* namespace ice */
