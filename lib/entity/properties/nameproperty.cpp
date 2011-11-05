/*
 * nameproperty.cpp
 *
 *  Created on: 1.11.2011
 *      Author: akin
 */

#include "nameproperty.h"

namespace ice
{

NameProperty::NameProperty()
: Property( PROPERTY_NAME_NAME )
{
}

NameProperty::~NameProperty()
{
}

void NameProperty::attach( Entity& entity )
{
	NameType::iterator iter = names.find( entity.id );
	if( iter != names.end() )
	{
		return;
	}

	names[ entity.id ];
}

void NameProperty::detach( Entity& entity )
{
	names.erase( entity.id );
}

std::string NameProperty::get( EntityKey entity )
{
	return names[ entity ];
}

} /* namespace ice */
