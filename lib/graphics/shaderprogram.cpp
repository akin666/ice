/*
 * shaderprogram.cpp
 *
 *  Created on: 19.4.2010
 *      Author: akin
 */

#include "shaderprogram.h"

#include <system/opengl>
#include <iostream>
#include <vector>
#include "attribute.h"
#include "uniform.h"
#include "shader.h"

#define NULL_PROGRAM 0

namespace ice
{
	void tryCreatingShaderProgram( unsigned int &id )
	{
		if( id == NULL_PROGRAM )
		{
			id = glCreateProgram();

			GL_TEST_ERROR("ShaderProgram tryCreatingShaderProgram")
		}
	}

	ShaderProgram::ShaderProgram()
	{
		m_id = NULL_PROGRAM;
		linking = false;
	}

	ShaderProgram::~ShaderProgram()
	{
		if( m_id != NULL_PROGRAM )
		{
			glDeleteProgram( m_id );
		}
	}

	unsigned int ShaderProgram::getId()
	{
		return m_id;
	}

	Attribute *ShaderProgram::insertAttribute( std::string key )
	{
		try
		{
			Attribute *att = new Attribute;
			att->setProgram( m_id );
			att->attach( key );
			attributes[key] = att;
			return att;
		}
		catch( ... ) {
		}
		return NULL;
	}

	Uniform *ShaderProgram::insertUniform( std::string key )
	{
		try
		{
			Uniform *uni = new Uniform;
			uni->setProgram( m_id );
			uni->attach( key );
			uniforms[key] = uni;
			return uni;
		}
		catch( ... ) {
		}
		return NULL;
	}

	Attribute *ShaderProgram::getAttribute( std::string key )
	{
		std::map< std::string , Attribute * >::iterator iter = attributes.find( key );

		if( iter == attributes.end() )
		{
			// Try to see if it has the uniform
			int m_fff = glGetAttribLocation( m_id , (const GLchar*)key.c_str() );

			if( m_fff < 0 )
			{
				Plattform::error(std::string("[attribute location not found] ") + key );
				return NULL;
			}

			return insertAttribute( key );
		}

		return iter->second;
	}

	Uniform *ShaderProgram::getUniform( std::string key )
	{
		std::map< std::string , Uniform * >::iterator iter = uniforms.find( key );

		if( iter == uniforms.end() )
		{
			// Try to see if it has the uniform
			int m_fff = glGetUniformLocation( m_id , (const GLchar*)key.c_str() );

			if( m_fff < 0 )
			{
				Plattform::error(std::string("[uniform location not found] ") + key );
				return NULL;
			}

			return insertUniform( key );
		}

		return iter->second;
	}

	void ShaderProgram::bind()
	{
		glUseProgram( m_id );
		GL_TEST_ERROR("ShaderProgram bind")
	}

	void ShaderProgram::bindDefault()
	{
		glUseProgram( 0 );
		GL_TEST_ERROR("ShaderProgram bindDefault")
	}

	// Shader creation functionality:
	void ShaderProgram::attach( Shader *piece )
	{
		if( piece == NULL )
		{
			std::cout << "Error, cannot attach NULL shader to program" << std::endl;
		}
		tryCreatingShaderProgram( m_id );
		linking = false;

		glAttachShader( m_id , piece->getId() );
		GL_TEST_ERROR("ShaderProgram insert")
	}

	void ShaderProgram::link()
	{
		glLinkProgram( m_id );
		GL_TEST_ERROR("ShaderProgram link")

		GLint tmp;
		glGetProgramiv( m_id , GL_LINK_STATUS , &tmp );
		if( tmp ) {
			linking = true;
		}
		else {
			linking = false;
		}
	}

	std::string ShaderProgram::getError()
	{
		if( m_id == NULL_PROGRAM )
		{
			return "";
		}

		GLint loglen = 0;
		glGetProgramiv( m_id , GL_INFO_LOG_LENGTH , &loglen );
		if (loglen > 0)
		{
			//GLchar* log = (GLchar*)malloc(sizeof(GLchar)*loglen);
			GLchar* log = new GLchar[loglen];
			glGetProgramInfoLog( m_id , loglen , NULL , log );

			std::string data( log );
			delete[] log;

			return data;
		}

		return "";
	}

	bool ShaderProgram::linked()
	{
		return (linking && m_id != NULL_PROGRAM);
	}
}
