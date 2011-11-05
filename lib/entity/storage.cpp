/*
 * storage.cpp
 *
 *  Created on: 16.10.2011
 *      Author: akin
 */

#include "storage"
#include <iterator>

namespace ice
{

std::deque< Property *> Storage::properties;
std::deque< Component *> Storage::components;

std::map< std::string , Component * > Storage::component_str;
std::map< std::string , Property * > Storage::property_str;

std::map< unsigned int , Component * > Storage::component_uint;
std::map< unsigned int , Property * > Storage::property_uint;

Property& Storage::getProperty( std::string name )
{
	std::map< std::string , Property * >::iterator iter = property_str.find( name );

	if( iter == property_str.end() )
	{
		throw;
	}

	return *iter->second;
}

Component& Storage::getComponent( std::string name )
{
	std::map< std::string , Component * >::iterator iter = component_str.find( name );

	if( iter == component_str.end() )
	{
		throw;
	}

	return *iter->second;
}

Property& Storage::getProperty( unsigned int id )
{
	std::map< unsigned int , Property * >::iterator iter = property_uint.find( id );

	if( iter == property_uint.end() )
	{
		throw;
	}

	return *iter->second;
}

Component& Storage::getComponent( unsigned int id )
{
	std::map< unsigned int , Component * >::iterator iter = component_uint.find( id );

	if( iter == component_uint.end() )
	{
		throw;
	}

	return *iter->second;
}

bool Storage::hasProperty( std::string name )
{
	return (property_str.find( name ) != property_str.end());
}

bool Storage::hasComponent( std::string name )
{
	return (component_str.find( name ) != component_str.end());
}

bool Storage::hasProperty( unsigned int id )
{
	return (property_uint.find( id ) != property_uint.end());
}

bool Storage::hasComponent( unsigned int id )
{
	return (component_uint.find( id ) != component_uint.end());
}

void Storage::add( Component *component )
{
	// Using name, instead of UINT, because the uint scheme
	// has not yet been solified/thought through.
	if( hasComponent( component->getName() ) )
	{
		// Already has such component.
		return;
	}

	components.push_back( component );
	component_str[ component->getName() ] = component;
	component_uint[ component->getId() ] = component;
}

void Storage::add( Property *property )
{
	// Using name, instead of UINT, because the uint scheme
	// has not yet been solified/thought through.
	if( hasProperty( property->getName() ) )
	{
		// Already has such property.
		return;
	}

	properties.push_back( property );
	property_str[ property->getName() ] = property;
	property_uint[ property->getId() ] = property;
}

} /* namespace ice */
