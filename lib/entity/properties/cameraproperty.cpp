/*
 * cameraproperty.cpp
 *
 *  Created on: 15.11.2011
 *      Author: akin
 */

#include "cameraproperty.h"
#include "../storage.h"

namespace ice
{

const std::string CameraProperty::KEY("camera");

CameraProperty::CameraProperty()
: Property( KEY ),
  current( Entity::NIL )
{
	positionProperty = Storage::createProperty<PositionProperty>();
}

CameraProperty::~CameraProperty()
{
}

void CameraProperty::attach( Entity& entity )
{
	CameraData::iterator iter = data.find( entity.id );
	if( iter != data.end() )
	{
		return;
	}
	if( current == Entity::NIL )
	{
		current = entity.id;
	}

	positionProperty->attach( entity );

	data[ entity.id ];
}

void CameraProperty::detach( Entity& entity )
{
	data.erase( entity.id );
}

void CameraProperty::setCurrentCamera( Entity& entity )
{
	current = entity.id;
}

void CameraProperty::setCurrentCamera( EntityKey& entity )
{
	current = entity;
}

CameraProperty::Data& CameraProperty::get( EntityKey key )
{
	return data[ key ];
}

} /* namespace ice */

