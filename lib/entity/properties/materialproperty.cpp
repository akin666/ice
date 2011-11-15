/*
 * materialproperty.cpp
 *
 *  Created on: 16.11.2011
 *      Author: akin
 */

#include "materialproperty.h"

namespace ice
{
const std::string MaterialProperty::KEY("material");

MaterialProperty::MaterialProperty()
: Property( KEY )
{
}

MaterialProperty::~MaterialProperty()
{
}
void MaterialProperty::attach( Entity& entity )
{
	MaterialData::iterator iter = data.find( entity.id );
	if( iter != data.end() )
	{
		return;
	}

	data[ entity.id ];
}

void MaterialProperty::detach( Entity& entity )
{
	data.erase( entity.id );
}

} /* namespace ice */

