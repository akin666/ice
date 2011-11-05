/*
 * uniform.cpp
 *
 *  Created on: 19.4.2010
 *      Author: akin
 */

#include "uniform.h"
#include <sys/opengl.h>
#include <sys/log.h>
#include <glm/transform>

namespace ice
{
	Uniform::Uniform()
	{
		m_program_id = 0;
	}

	Uniform::~Uniform()
	{
	}

	void Uniform::setProgram( unsigned int program )
	{
		m_program_id = program;
	}

	void Uniform::attach( std::string name )
	{
		m_name = name;

		m_uniform_id = glGetUniformLocation( m_program_id , (const GLchar*)name.c_str() );

		if( m_uniform_id < 0 )
		{
			LOG_ERROR( std::string("Uniform not found ") + name );
		}

		GL_TEST_ERROR("Uniform attach")
	}

	std::string Uniform::getName()
	{
		return m_name;
	}

	void Uniform::set(float v)
	{
		glUniform1f( m_uniform_id , v );
		GL_TEST_ERROR("Uniform set float")
	}
	void Uniform::set(float v, float v2)
	{
		glUniform2f( m_uniform_id , v , v2 );
		GL_TEST_ERROR("Uniform set float v1v2")
	}
	void Uniform::set(float v, float v2, float v3)
	{
		glUniform3f( m_uniform_id , v , v2 , v3 );
		GL_TEST_ERROR("Uniform set float v1v2v3")
	}
	void Uniform::set(float v, float v2, float v3, float v4)
	{
		glUniform4f( m_uniform_id , v , v2 , v3 , v4 );
		GL_TEST_ERROR("Uniform set float v1v2v3v4")
	}
	void Uniform::set(int v)
	{
		glUniform1i( m_uniform_id , v );
		GL_TEST_ERROR("Uniform set int")
	}
	void Uniform::set(int v, int v2)
	{
		glUniform2i( m_uniform_id , v , v2 );
		GL_TEST_ERROR("Uniform set int v1v2")
	}
	void Uniform::set(int v, int v2, int v3)
	{
		glUniform3i( m_uniform_id , v , v2 , v3 );
		GL_TEST_ERROR("Uniform set int v1v2v3")
	}
	void Uniform::set(int v, int v2, int v3, int v4)
	{
		glUniform4i( m_uniform_id , v , v2 , v3 , v4 );
		GL_TEST_ERROR("Uniform set int v1v2v3v4")
	}
	void Uniform::set(float *v, int size)
	{
		glUniform1fv( m_uniform_id , size , v );
		GL_TEST_ERROR("Uniform set float*")
	}
	void Uniform::set2(float *v, int size)
	{
		glUniform2fv( m_uniform_id , size , v );
		GL_TEST_ERROR("Uniform set2 float*")
	}
	void Uniform::set3(float *v, int size)
	{
		glUniform3fv( m_uniform_id , size , v );
		GL_TEST_ERROR("Uniform set3 float*")
	}
	void Uniform::set4(float *v, int size)
	{
		glUniform4fv( m_uniform_id , size , v );
		GL_TEST_ERROR("Uniform set4 float*")
	}
	void Uniform::set(int *v, int size)
	{
		glUniform1iv( m_uniform_id , size , v );
		GL_TEST_ERROR("Uniform set int*")
	}
	void Uniform::set2(int *v, int size)
	{
		glUniform2iv( m_uniform_id , size , v );
		GL_TEST_ERROR("Uniform set2 int*")
	}
	void Uniform::set3(int *v, int size)
	{
		glUniform3iv( m_uniform_id , size , v );
		GL_TEST_ERROR("Uniform set3 int*")
	}
	void Uniform::set4(int *v, int size)
	{
		glUniform4iv( m_uniform_id , size , v );
		GL_TEST_ERROR("Uniform set4 int*")
	}
	void Uniform::setMatrix4( const float *v , int size )
	{
		glUniformMatrix4fv( m_uniform_id , size , GL_FALSE , v );
		GL_TEST_ERROR("Uniform setMatrix4 float*")
	}

	void Uniform::set( const glm::mat4x4& matrix )
	{
		glUniformMatrix4fv( m_uniform_id , 1 , GL_FALSE , &matrix[0][0] );
		GL_TEST_ERROR("Uniform set glm::mat4x4")
	}
	void Uniform::set( const glm::vec2& vec )
	{
		glUniform2f( m_uniform_id , vec.x , vec.y );
		GL_TEST_ERROR("Uniform set glm::vec2")
	}
	void Uniform::set( const glm::vec3& vec )
	{
		glUniform3f( m_uniform_id , vec.x , vec.y , vec.z );
		GL_TEST_ERROR("Uniform set glm::vec3")
	}
	void Uniform::set( const glm::vec4& vec )
	{
		glUniform4f( m_uniform_id , vec.x , vec.y , vec.z , vec.w );
		GL_TEST_ERROR("Uniform set glm::vec4")
	}
	void Uniform::set( const glm::ivec2& vec )
	{
		glUniform2i( m_uniform_id , vec.x , vec.y );
		GL_TEST_ERROR("Uniform set glm::ivec2")
	}
	void Uniform::set( const glm::ivec3& vec )
	{
		glUniform3i( m_uniform_id , vec.x , vec.y , vec.z );
		GL_TEST_ERROR("Uniform set glm::ivec3")
	}
	void Uniform::set( const glm::ivec4& vec )
	{
		glUniform4i( m_uniform_id , vec.x , vec.y , vec.z , vec.w );
		GL_TEST_ERROR("Uniform set glm::ivec4")
	}

	void Uniform::bindTexture( int texture_unit , unsigned int texture_id )
	{
		// Bind the texture
		glActiveTexture( GL_TEXTURE0 + texture_unit );
		glBindTexture(GL_TEXTURE_2D, texture_id );
		// Set the sampler texture unit
		glUniform1i(m_uniform_id, texture_unit );

		GL_TEST_ERROR("Uniform bindTexture")
	}

	void Uniform::bindTexture( const Texture& texture , int texture_unit )
	{
		// Bind the texture
		glActiveTexture( GL_TEXTURE0 + texture_unit );
		glBindTexture(GL_TEXTURE_2D, texture.getId() );
		// Set the sampler texture unit
		glUniform1i(m_uniform_id, texture_unit );

		GL_TEST_ERROR("Uniform bindTexture Texture")
	}
}


