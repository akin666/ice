/*
 * cfgparser.h
 *
 *  Created on: 14.5.2009
 *      Author: akin
 */

#ifndef ICE_CONFIG_H_
#define ICE_CONFIG_H_

#include <iostream>
#include <map>

namespace ice
{
	class DIO;

	class Config
	{
	protected:
		std::map< std::string , std::string > pairs;
	public:
		Config();
		Config( std::string );
		virtual ~Config();

		std::string get( const std::string& key );

		bool isSet( const std::string key );

		void set( std::string key , std::string value );
		void remove( std::string key );

		virtual float getf( const std::string key , const float def );
		virtual bool getb( const std::string key , const bool def );
		virtual int geti( const std::string key , const int def );
		virtual std::string gets( const std::string key , const std::string def );

		bool load( DIO& dio );
		bool load( std::string path );
		bool save( std::string path );
	};
}

#endif /* ICE_CONFIG_H_ */
