/*
 * storage.h
 *
 *  Created on: 16.10.2011
 *      Author: akin
 */

#ifndef STORAGE_H_
#define STORAGE_H_

#include "property"
#include "component"
#include <deque>
#include <map>
#include <iostream>

namespace ice
{

class Storage
{
private:
	static std::deque< Property *> properties;
	static std::deque< Component *> components;

	static std::map< std::string , Component * > component_str;
	static std::map< std::string , Property * > property_str;

	static std::map< unsigned int , Component * > component_uint;
	static std::map< unsigned int , Property * > property_uint;
public:
	static Property& getProperty( std::string name );

	static Component& getComponent( std::string name );

	static Property& getProperty( unsigned int id );

	static Component& getComponent( unsigned int id );

	template<class ctype>
	static ctype& getProperty( std::string name );

	template<class ctype>
	static ctype& getComponent( std::string name );

	template<class ctype>
	static ctype& getProperty( unsigned int id );

	template<class ctype>
	static ctype& getComponent( unsigned int id );

	static bool hasProperty( std::string name );
	static bool hasComponent( std::string name );

	static bool hasProperty( unsigned int id );
	static bool hasComponent( unsigned int id );

	static void add( Component *component );
	static void add( Property *property );

	template <class PropertyType>
	static PropertyType *createProperty( std::string name );
};


template<class ctype>
ctype& Storage::getProperty( std::string name )
{
	std::map< std::string , Property * >::iterator iter = property_str.find( name );

	if( iter == property_str.end() )
	{
		throw;
	}

	ctype *conv = dynamic_cast<ctype*>( iter->second );

	if( conv == NULL )
	{
		throw;
	}

	return *conv;
}

template<class ctype>
ctype& Storage::getComponent( std::string name )
{
	std::map< std::string , Component * >::iterator iter = component_str.find( name );

	if( iter == component_str.end() )
	{
		throw;
	}

	ctype *conv = dynamic_cast<ctype*>( iter->second );

	if( conv == NULL )
	{
		throw;
	}

	return *conv;
}

template<class ctype>
ctype& Storage::getProperty( unsigned int id )
{
	std::map< unsigned int , Property * >::iterator iter = property_uint.find( id );

	if( iter == property_uint.end() )
	{
		throw;
	}

	ctype *conv = dynamic_cast<ctype*>( iter->second );

	if( conv == NULL )
	{
		throw;
	}

	return *conv;
}

template<class ctype>
ctype& Storage::getComponent( unsigned int id )
{
	std::map< unsigned int , Component * >::iterator iter = component_uint.find( id );

	if( iter == component_uint.end() )
	{
		throw;
	}

	ctype *conv = dynamic_cast<ctype*>( iter->second );

	if( conv == NULL )
	{
		throw;
	}

	return *conv;
}

template <class PropertyType>
PropertyType *Storage::createProperty( std::string name )
{
	std::map< std::string , Property * >::iterator iter = property_str.find( name );

	PropertyType *ret;
	if( iter == property_str.end() )
	{
		ret = new PropertyType;
		add( ret );
	}
	else
	{
		ret = dynamic_cast<PropertyType*>( iter->second );
	}
	return ret;
}

} /* namespace ice */
#endif /* STORAGE_H_ */
