/*
 * weightproperty.cpp
 *
 *  Created on: 2.11.2011
 *      Author: akin
 */

#include "weightproperty.h"
#include <entity/entity>

namespace ice
{

WeightProperty::WeightProperty()
: Property( PROPERTY_WEIGHT_NAME )
{
}

WeightProperty::~WeightProperty()
{
}

void WeightProperty::attach( Entity& entity )
{
	WeightType::iterator iter = weightData.find( entity.id );
	if( iter != weightData.end() )
	{
		return;
	}

	weightData[ entity.id ];
}

void WeightProperty::detach( Entity& entity )
{
	weightData.erase( entity.id );
}

float& WeightProperty::get( EntityKey key )
{
	return weightData[ key ];
}

WeightProperty::WeightType& WeightProperty::getTime()
{
	return weightData;
}

} /* namespace ice */
