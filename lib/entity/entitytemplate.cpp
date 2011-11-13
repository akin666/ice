/*
 * entitytemplate.cpp
 *
 *  Created on: 9.11.2011
 *      Author: akin
 */

#include "entitytemplate"

namespace ice
{

unsigned int EntityTemplate::s_id = 1;

unsigned int EntityTemplate::genId()
{
	return s_id++;
}

EntityTemplate::EntityTemplate( std::string name )
: sm_id( genId() ),
  name( name )
{
}

EntityTemplate::~EntityTemplate()
{
}

std::string EntityTemplate::getName()
{
	return name;
}

unsigned int EntityTemplate::getId() const
{
	return sm_id;
}

Entity EntityTemplate::create()
{
	Entity entity;
	attach( entity );
	return entity;
}

void EntityTemplate::attach( Entity& entity )
{
}

} /* namespace ice */
