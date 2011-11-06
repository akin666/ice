/*
 * global.h
 *
 *  Created on: 24.7.2011
 *      Author: akin
 */

#ifndef ICE_GLOBAL_H_
#define ICE_GLOBAL_H_

#include <map>
#include <iterator>
#include <string>
#include <vector>

namespace ice
{
	template <class ctype>
	class Global
	{
	protected:
		static std::map< std::string , ctype * > data;

		static Global *current;
	public:
		static void set( const std::string key , ctype *ptr );
		static ctype *get( const std::string key );
		static bool has( const std::string key );

		static void getKeys( std::vector<std::string>& keys );

		static void clear();
		static void remove( const std::string key );
	};

	template <class ctype>
	Global<ctype> *Global<ctype>::current;

	template <class ctype>
	std::map< std::string , ctype * > Global<ctype>::data;

	template <class ctype>
	void Global<ctype>::set( const std::string key , ctype *ptr )
	{
		data[ key ] = ptr;
	}

	template <class ctype>
	ctype *Global<ctype>::get( const std::string key )
	{
		typename std::map< std::string , ctype*>::iterator iter = data.find( key );

		if( iter != data.end() )
		{
			return iter->second;
		}
		return NULL;
	}

	template <class ctype>
	bool Global<ctype>::has( const std::string key )
	{
		typename std::map< std::string , ctype*>::iterator iter = data.find( key );
		return iter != data.end();
	}

	template <class ctype>
	void Global<ctype>::getKeys(  std::vector<std::string>& keys )
	{
		keys.clear();
		keys.reserve( data.size() );

		for( typename std::map< std::string , ctype * >::iterator iter = data.begin() ; iter != data.end() ; ++iter )
		{
			keys.push_back( iter->first );
		}
	}

	template <class ctype>
	void Global<ctype>::clear()
	{
		for( typename std::map< std::string , ctype * >::iterator iter = data.begin() ; iter != data.end() ; ++iter )
		{
			delete iter->second;
		}
		data.clear();
	}

	template <class ctype>
	void Global<ctype>::remove( const std::string key )
	{
		typename std::map< std::string , ctype * >::iterator iter = data.find( key );
		if( iter != data.end())
		{
			delete iter->second;
			data.erase( iter );
		}
	}
} /* namespace ice */

#endif /* ICE_GLOBAL_H_ */
