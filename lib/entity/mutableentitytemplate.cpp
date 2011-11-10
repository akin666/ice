/*
 * mutableentitytemplate.cpp
 *
 *  Created on: 9.11.2011
 *      Author: akin
 */

#include "mutableentitytemplate"

namespace ice
{

MutableEntityTemplate::MutableEntityTemplate( std::string name )
: EntityTemplate( name )
{
}

MutableEntityTemplate::~MutableEntityTemplate()
{
}

void MutableEntityTemplate::setName( std::string name )
{
	this->name = name;
}

void MutableEntityTemplate::attach( Component& component )
{
	components.push_back( &component );
}

void MutableEntityTemplate::attach( EntityTemplate& tpl )
{
	templates.push_back( &tpl );
}

void MutableEntityTemplate::attach( Entity& entity )
{
	// Attach this templates components.
	for( int i = components.size() - 1 ; i >= 0 ; --i )
	{
		components.at( i )->attach( entity );
	}
	// Attach slave templates components.
	for( int i = templates.size() - 1 ; i >= 0 ; --i )
	{
		templates.at( i )->attach( entity );
	}
}

} /* namespace ice */
