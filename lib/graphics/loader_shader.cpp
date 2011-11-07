/*
 * loader_texture.cpp
 *
 *  Created on: 6.3.2011
 *      Author: akin
 */

#include "loader.h"
#include <vector>
#include <system/opengl>
#include <log/log> // log
#include <dio/filedio> // binary file access

namespace ice
{
	namespace loader
	{// Shader
		Shader *loadShader( const Shader::Type type , const std::string path )
		{
			FileDIO dio( path );
			return loadShader( type , dio );
		}

		Shader *loadShader( const Shader::Type type , DIO& dio )
		{
			return loadShader( type , dio , dio.getDataSize() );
		}

		Shader *loadShader( const Shader::Type type , DIO& dio , int length )
		{
			std::vector<unsigned char> buffer(length);
			int readCount = dio.readBlock( &buffer[0] , length );

			if( readCount != length )
			{
				// Read inconsistant amount of data.
				return NULL;
			}

			Shader *shader = new Shader;

			shader->setType( type );

			if( !shader->load( &buffer[0] , buffer.size() ) )
			{
				delete shader;
				return NULL;
			}

			return shader;
		}
	}
}
