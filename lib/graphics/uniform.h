/*
 * uniform.h
 *
 *  Created on: 19.4.2010
 *      Author: akin
 */

#ifndef UNIFORM_H_
#define UNIFORM_H_

#include <iostream>
#include <glm/glm>
#include "texture.h"

namespace ice
{

	class Uniform
	{
	protected:
		unsigned int m_program_id;
		int m_uniform_id;
		std::string m_name;
	public:
		Uniform( );
		virtual ~Uniform();

		void setProgram( unsigned int program );
		void attach( std::string name );
		std::string getName();

		void set( float v );
		void set( float v , float v2 );
		void set( float v , float v2 , float v3 );
		void set( float v , float v2 , float v3 , float v4 );
		void set( int v );
		void set( int v , int v2 );
		void set( int v , int v2 , int v3 );
		void set( int v , int v2 , int v3 , int v4 );

		void set( float *v , int size );
		void set2( float *v , int size );
		void set3( float *v , int size );
		void set4( float *v , int size );
		void set( int *v , int size );
		void set2( int *v , int size );
		void set3( int *v , int size );
		void set4( int *v , int size );

		void setMatrix4( const float *v , int size );

		void set( const glm::mat4x4& matrix );
		void set( const glm::vec2& vec );
		void set( const glm::vec3& vec );
		void set( const glm::vec4& vec );
		void set( const glm::ivec2& vec );
		void set( const glm::ivec3& vec );
		void set( const glm::ivec4& vec );

		void bindTexture( int texture_unit , unsigned int texture_id );
		void bindTexture( const Texture& texture , int texture_unit = 0 );
	};
}

#endif /* UNIFORM_H_ */
