/*
 * shader.cpp
 *
 *  Created on: 19.4.2010
 *      Author: akin
 */

#include "shader.h"
#include <sys/opengl.h>

#define NULL_SHADER 0

namespace ice
{
	Shader::Shader( )
	{
		id = NULL_SHADER;
		m_type = UNKNOWN;
	}

	Shader::~Shader()
	{
		if( id != NULL_SHADER )
		{
			glDeleteShader( id );
			id = NULL_SHADER;
		}
	}

	void Shader::setType( Type type )
	{
		m_type = type;
	}

	void Shader::setTypeString( std::string type )
	{
		if( type == "fragment" )
		{
			setType( FRAGMENT );
		}
		else if( type == "vertex" )
		{
			setType( VERTEX );
		}
#if defined(GL_GEOMETRY_SHADER) or defined(GL_GEOMETRY_SHADER_EXT)
		else if( type == "geometry" )
		{
			setType( GEOMETRY );
		}
#endif
#if defined(GL_TESS_CONTROL_SHADER) or defined(GL_TESS_CONTROL_SHADER_EXT)
		else if( type == "control" )
		{
			setType( CONTROL );
		}
#endif
#if defined(GL_TESS_EVALUATION_SHADER) or defined(GL_TESS_EVALUATION_SHADER_EXT)
		else if( type == "evaluation" )
		{
			setType( EVALUATION );
		}
#endif
	}

	unsigned int Shader::getId()
	{
		return id;
	}

	bool Shader::load( const unsigned char *data , int length )
	{
		switch( m_type )
		{
			case Shader::VERTEX :
			{
				id = glCreateShader( GL_VERTEX_SHADER );
				break;
			}
			case Shader::FRAGMENT :
			{
				id = glCreateShader( GL_FRAGMENT_SHADER );
				break;
			}
	#if defined(GL_GEOMETRY_SHADER)
			case Shader::GEOMETRY :
			{
				id = glCreateShader( GL_GEOMETRY_SHADER );
				break;
			}
	#elif defined(GL_GEOMETRY_SHADER_EXT)
			case Shader::GEOMETRY :
			{
				id = glCreateShader( GL_GEOMETRY_SHADER_EXT );
				break;
			}
	#endif
	#if defined(GL_TESS_CONTROL_SHADER)
			case Shader::CONTROL :
			{
				id = glCreateShader( GL_TESS_CONTROL_SHADER );
				break;
			}
	#elif defined(GL_TESS_CONTROL_SHADER_EXT)
			case Shader::CONTROL :
			{
				id = glCreateShader( GL_TESS_CONTROL_SHADER_EXT );
				break;
			}
	#endif
	#if defined(GL_TESS_EVALUATION_SHADER)
			case Shader::EVALUATION :
			{
				id = glCreateShader( GL_TESS_EVALUATION_SHADER );
				break;
			}
	#elif defined(GL_TESS_EVALUATION_SHADER_EXT)
			case Shader::CONTROL :
			{
				id = glCreateShader( GL_TESS_EVALUATION_SHADER_EXT );
				break;
			}
	#endif
			default :
			{
				return false;
			}
		}

		const char *dat = (char *)data;

		glShaderSource( id , 1 , (const GLchar**)&dat , &length );
		glCompileShader( id );

		GL_TEST_ERROR("load_shader. ")

		GLint tmp;
		glGetShaderiv( id , GL_COMPILE_STATUS , &tmp );

		if( tmp )
		{
			// ALL OK!
			return true;
		}

		// ERROR!
		GLint loglen = 0;
		glGetShaderiv(id  , GL_INFO_LOG_LENGTH , &loglen );
		if (loglen > 0)
		{
			GLchar* log = new GLchar[loglen];
			glGetShaderInfoLog( id , loglen , NULL , log );

			LOG_ERROR( std::string(log) );

			delete[] log;
		}
		return false;
	}
}
