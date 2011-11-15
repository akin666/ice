/*
 * entity.cpp
 *
 *  Created on: 14.10.2011
 *      Author: akin
 */

#include "entity"

namespace ice
{

EntityKey Entity::s_id = 0xFF;
const EntityKey Entity::NIL = 0x0;

unsigned int Entity::genId()
{
	return s_id++;
}

Entity::Entity()
: id( genId() )
{
}

Entity::Entity( const Entity& other )
: id( other.id )
{
}

Entity::Entity( EntityKey key )
: id( key )
{
}

Entity::~Entity()
{
}

} /* namespace ice */
