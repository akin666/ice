/*
 * loader_texture.cpp
 *
 *  Created on: 6.3.2011
 *      Author: akin
 */

#include "loader.h"
#include <vector>
#include <system/opengl> // gl
#include <system/random> // random
#include <libwrapper.h> // stb_image functions
#include <dio/filedio.h> // binary file access
#include <system/global>
#include "texture/texturegroup.h"
#include <glm/glm>

namespace ice
{
	namespace loader
	{
		bool loadTexture( const std::string zone , const std::string name , const std::string path )
		{
			FileDIO dio( path );
			return loadTexture( zone , name , dio );
		}

		bool loadTexture( const std::string zone , const std::string name , DIO& dio )
		{
			return loadTexture( zone , name , dio , dio.getDataSize() );
		}

		bool loadTexture( const std::string zone , const std::string name , DIO& dio , int length )
		{
			std::vector<unsigned char> buffer(length);
			int readCount = dio.readBlock( &buffer[0] , length );

			if( readCount != length )
			{
				// Read inconsistant amount of data.
				return false;
			}

			int width;
			int height;
			int channels = 4;
			unsigned char *image_data = loadImage( buffer ,width , height ,channels );

			if( width < 1 || height < 1 || channels < 1 )
			{
				freeImageData( image_data );
				return false;
			}

			Texture *texture = Global<Texture>::get( name );

			// Collision,
			// The texture already exists
			if( texture != NULL )
			{
				freeImageData( image_data );
				return false;
			}

			TextureGroup *group = Global<TextureGroup>::get( zone );

			// Group does not exist.
			// create one.
			if( group == NULL )
			{
				group = new TextureGroup;
				group->initialize( 2048 , 2048 , 1 , RGBA );
				Global<TextureGroup>::set( zone , group );
			}

			// Create texture.
			texture = new Texture;
			texture->getDimension() = glm::ivec2( width , height );

			// request failed,
			// KILL EM ALL
			if( !group->request( *texture ) )
			{
				freeImageData( image_data );
				delete texture;
				return false;
			}

			texture->getG()->renderSubTexture( texture->getPosition() , texture->getDimension() , image_data );

			Global<Texture>::set( name , texture );

			freeImageData( image_data );

			return true;
		}


		GTexture *loadTexture( std::string path )
		{
			FileDIO dio( path );
			return loadTexture( dio );
		}

		GTexture *loadTexture( DIO& dio )
		{
			return loadTexture( dio , dio.getDataSize() );
		}

		GTexture *loadTexture( DIO& dio , int length )
		{
			std::vector<unsigned char> buffer(length);
			int readCount = dio.readBlock( &buffer[0] , length );

			if( readCount != length )
			{
				// Read inconsistant amount of data.
				return NULL;
			}

			int width;
			int height;
			int channels = 4;
			unsigned char *image_data = loadImage( buffer ,width , height ,channels );

			if( width < 1 || height < 1 || channels < 1 )
			{
				freeImageData( image_data );
				return false;
			}

			ColorMode mode = RGBA;

			switch( channels )
			{
				case 4 : mode = RGBA; break;
				case 3 : mode = RGB; break;
				default : break;
			}

			GTexture *ret = loadTexture( width , height , mode , image_data );

			freeImageData( image_data );

			return ret;
		}

		GTexture *randomTexture( int width , int height )
		{
			std::vector<unsigned char> image_data;

			unsigned int size = width * height * 4;
			image_data.reserve(size);

			Random *random = &(Random::get());

			for (unsigned int i = 0; i < size; i++) {
				image_data.push_back(random->getUChar());
			}

			return loadTexture( width, height, RGBA , &image_data[0] );
		}

		GTexture *loadTexture( const int width , const unsigned int height , const ColorMode mode , const unsigned char *data )
		{
			GTexture *tex = new GTexture;

			tex->setWidth( width ).setHeight( height ).setColorMode( mode ).initialize( data );

			return tex;
		}
	}
}
