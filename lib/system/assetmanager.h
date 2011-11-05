/*
 * assetmanager.h
 *
 *  Created on: 24.7.2011
 *      Author: akin
 */

#ifndef ASSETMANAGER_H_
#define ASSETMANAGER_H_

#include <map>
#include <iterator>
#include <string>
#include <vector>

namespace ice
{
	template <class ctype>
	class AssetManager
	{
	protected:
		static std::map< std::string , ctype * > data;

		static AssetManager *current;
	public:
		static void set( const std::string key , ctype *ptr );
		static ctype *get( const std::string key );
		static bool has( const std::string key );

		static void getKeys( std::vector<std::string>& keys );

		static void clear();
		static void remove( const std::string key );
	};

	template <class ctype>
	AssetManager<ctype> *AssetManager<ctype>::current;

	template <class ctype>
	std::map< std::string , ctype * > AssetManager<ctype>::data;

	template <class ctype>
	void AssetManager<ctype>::set( const std::string key , ctype *ptr )
	{
		data[ key ] = ptr;
	}

	template <class ctype>
	ctype *AssetManager<ctype>::get( const std::string key )
	{
		typename std::map< std::string , ctype*>::iterator iter = data.find( key );

		if( iter != data.end() )
		{
			return iter->second;
		}
		return NULL;
	}

	template <class ctype>
	bool AssetManager<ctype>::has( const std::string key )
	{
		typename std::map< std::string , ctype*>::iterator iter = data.find( key );
		return iter != data.end();
	}

	template <class ctype>
	void AssetManager<ctype>::getKeys(  std::vector<std::string>& keys )
	{
		keys.clear();
		keys.reserve( data.size() );

		for( typename std::map< std::string , ctype * >::iterator iter = data.begin() ; iter != data.end() ; ++iter )
		{
			keys.push_back( iter->first );
		}
	}

	template <class ctype>
	void AssetManager<ctype>::clear()
	{
		for( typename std::map< std::string , ctype * >::iterator iter = data.begin() ; iter != data.end() ; ++iter )
		{
			delete iter->second;
		}
		data.clear();
	}

	template <class ctype>
	void AssetManager<ctype>::remove( const std::string key )
	{
		typename std::map< std::string , ctype * >::iterator iter = data.find( key );
		if( iter != data.end())
		{
			delete iter->second;
			data.erase( iter );
		}
	}
} /* namespace ice */

#endif /* ASSETMANAGER_H_ */
