/*well
 * Loader.h
 *
 *  Created on: 6.3.2011
 *      Author: akin
 */

#ifndef LOADER_H_
#define LOADER_H_

#include "texture/gtexture.h"
#include "shader/shader.h"
#include <font/font.h>
#include <dio/dio>

namespace ice
{
	namespace loader
	{
		// Texture
		GTexture *loadTexture( std::string path );
		GTexture *loadTexture( DIO& dio );
		GTexture *loadTexture( DIO& dio , int length );
		GTexture *randomTexture( int width , int height );

		// Texture Name Dio Path
		bool loadTexture( const std::string zone , const std::string name , const std::string path );
		bool loadTexture( const std::string zone , const std::string name , DIO& dio );
		bool loadTexture( const std::string zone , const std::string name , DIO& dio , int length );

		// The ownership of unsigned char data DOES NOT transfer here
		GTexture *loadTexture( const int width , const unsigned int height , const ColorMode mode  , const unsigned char *data );

		// Shader
		Shader *loadShader( const Shader::Type type , const std::string path );
		Shader *loadShader( const Shader::Type type , DIO& dio );
		Shader *loadShader( const Shader::Type type , DIO& dio , int length );
		// The ownership of unsigned char data DOES NOT transfer here
		Shader *loadShader( const Shader::Type type , unsigned char *data , int length );

		// Font
		Font *loadFont( DIO& dio , int size );
	}
}

#endif /* LOADER_H_ */
