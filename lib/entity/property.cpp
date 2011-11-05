/*
 * property.cpp
 *
 *  Created on: 14.10.2011
 *      Author: akin
 */

#include "property"

namespace ice
{

unsigned int Property::sm_id = 1;

unsigned int Property::getNewId()
{
	return sm_id++;
}

Property::Property( std::string name )
: id( getNewId() ),
  name( name )
{
}

Property::~Property()
{
}

std::string Property::getName() const
{
	return name;
}

unsigned int Property::getId() const
{
	return id;
}

} /* namespace ice */
