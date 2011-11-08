/*
 * entitytemplate.cpp
 *
 *  Created on: 9.11.2011
 *      Author: akin
 */

#include "entitytemplate"

namespace ice
{

EntityTemplate::EntityTemplate()
{
}

EntityTemplate::~EntityTemplate()
{
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
