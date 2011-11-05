/*
 * attribute.cpp
 *
 *  Created on: 19.4.2010
 *      Author: akin
 */

#include "attribute.h"
#include <iostream>

namespace ice
{
	Attribute::Attribute( )
	{
		m_program_id = 0;
	}

	Attribute::~Attribute()
	{
	}

	void Attribute::setProgram( unsigned int program )
	{
		m_program_id = program;
	}

	void Attribute::attach( std::string name )
	{
		m_name = name;

		m_attribute_id = glGetAttribLocation( m_program_id , (const GLchar*)name.c_str() );

		if( m_attribute_id < 0 )
		{
			Plattform::error(std::string("[in attribute vertex location not found] ") + name );
		}

		GL_TEST_ERROR("[in vertex attribute attach]")
	}

	std::string Attribute::getName()
	{
		return m_name;
	}

	void Attribute::enable()
	{
		glEnableVertexAttribArray( m_attribute_id );
		GL_TEST_ERROR("[in attribute vertex enable]")
	}

	void Attribute::disable()
	{
		glDisableVertexAttribArray( m_attribute_id );
		GL_TEST_ERROR("[in attribute vertex disable]")
	}

	void Attribute::setPointer( int data_size , GLenum data_type , GLsizei stride )
	{
		//glEnableVertexAttribArray(0);
		//We like submitting vertices on stream 0 for no special reason //The starting point of the VBO, for the vertices
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MyVertex), BUFFER_OFFSET(0));
		//glEnableVertexAttribArray(1);
		//We like submitting normals on stream 1 for no special reason //The starting point of normals, 12 bytes away
		//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(MyVertex), BUFFER_OFFSET(12));
		//glEnableVertexAttribArray(2);
		//We like submitting texcoords on stream 2 for no special reason //The starting point of texcoords, 24 bytes away
		//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(MyVertex), BUFFER_OFFSET(24));
		// A (starting point), How many datas, normalized?, size of whole element (0=packed data), position in data ??
	//	glBindBuffer( GL_ARRAY_BUFFER , buffer_id );
		glEnableVertexAttribArray( m_attribute_id );
		// GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer
		glVertexAttribPointer( m_attribute_id , data_size , data_type , GL_FALSE , stride , NULL );
		//glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
		//glEnableVertexAttribArray(VETEX_POS_INDX);
		//glVertexAttribPointer(VERTEX_POS_INDX, VERTEX_POS_SIZE, GL_FLOAT, GL_FALSE, vtxStrides[0], 0);
	}

	void Attribute::setPointer(int size, GLenum type, void *ptr)
	{
		// glVertexAttribPointer( GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer);
		glVertexAttribPointer( 0 , size, type, GL_FALSE , 0 , ptr );
		GL_TEST_ERROR("[in] vertex pointer")
	}

	void Attribute::set(float v)
	{
		glVertexAttrib1f( m_attribute_id , v );
		GL_TEST_ERROR("[in] vertexset")
	}
	void Attribute::set(float v, float v2)
	{
		glVertexAttrib2f( m_attribute_id , v , v2 );
		GL_TEST_ERROR("[in] vertex set")
	}
	void Attribute::set(float v, float v2, float v3)
	{
		glVertexAttrib3f( m_attribute_id , v , v2 , v3 );
		GL_TEST_ERROR("[in] vertex set")
	}
	void Attribute::set(float v, float v2, float v3, float v4)
	{
		glVertexAttrib4f( m_attribute_id , v , v2 , v3 , v4 );
		GL_TEST_ERROR("[in] vertex set")
	}
	void Attribute::set(double v)
	{
		glVertexAttrib1d( m_attribute_id , v );
		GL_TEST_ERROR("[in] vertex set")
	}
	void Attribute::set(double v, double v2)
	{
		glVertexAttrib2d( m_attribute_id , v , v2 );
		GL_TEST_ERROR("[in] vertex set")
	}
	void Attribute::set(double v, double v2, double v3)
	{
		glVertexAttrib3d( m_attribute_id , v , v2 , v3 );
		GL_TEST_ERROR("[in] vertex set")
	}
	void Attribute::set(double v, double v2, double v3, double v4)
	{
		glVertexAttrib4d( m_attribute_id , v , v2 , v3 , v4 );
		GL_TEST_ERROR("[in] vertex set")
	}
	void Attribute::set(short v)
	{
		glVertexAttrib1s( m_attribute_id , v );
		GL_TEST_ERROR("[in] vertex set")
	}
	void Attribute::set(short v, short v2)
	{
		glVertexAttrib2s( m_attribute_id , v , v2 );
		GL_TEST_ERROR("[in] vertex set")
	}
	void Attribute::set(short v, short v2, short v3)
	{
		glVertexAttrib3s( m_attribute_id , v , v2 , v3 );
		GL_TEST_ERROR("[in] vertex set")
	}
	void Attribute::set(short v, short v2, short v3, short v4)
	{
		glVertexAttrib4s( m_attribute_id , v , v2 , v3 , v4 );
		GL_TEST_ERROR("[in] vertex set")
	}

	void Attribute::set(float *v)
	{
		glVertexAttrib1fv( m_attribute_id , v );
		GL_TEST_ERROR("[in] vertex set")
	}
	void Attribute::set2(float *v)
	{
		glVertexAttrib2fv( m_attribute_id , v );
		GL_TEST_ERROR("[in] vertex set")
	}
	void Attribute::set3(float *v)
	{
		glVertexAttrib3fv( m_attribute_id , v );
		GL_TEST_ERROR("[in] vertex set")
	}
	void Attribute::set4(float *v)
	{
		glVertexAttrib4fv( m_attribute_id , v );
		GL_TEST_ERROR("[in] vertex set")
	}

	void Attribute::set(double *v)
	{
		glVertexAttrib1dv( m_attribute_id , v );
		GL_TEST_ERROR("[in] vertex set")
	}
	void Attribute::set2(double *v)
	{
		glVertexAttrib2dv( m_attribute_id , v );
		GL_TEST_ERROR("[in] vertex set")
	}
	void Attribute::set3(double *v)
	{
		glVertexAttrib3dv( m_attribute_id , v );
		GL_TEST_ERROR("[in] vertex set")
	}
	void Attribute::set4(double *v)
	{
		glVertexAttrib4dv( m_attribute_id , v );
		GL_TEST_ERROR("[in] vertex set")
	}

	void Attribute::set(short *v)
	{
		glVertexAttrib1sv( m_attribute_id , v );
		GL_TEST_ERROR("[in] vertex set")
	}
	void Attribute::set2(short *v)
	{
		glVertexAttrib2sv( m_attribute_id , v );
		GL_TEST_ERROR("[in] vertex set")
	}
	void Attribute::set3(short *v)
	{
		glVertexAttrib3sv( m_attribute_id , v );
		GL_TEST_ERROR("[in] vertex set")
	}
	void Attribute::set4(short *v)
	{
		glVertexAttrib4sv( m_attribute_id , v );
		GL_TEST_ERROR("[in] vertex set")
	}

	void Attribute::set4(int *v)
	{
		glVertexAttrib4iv( m_attribute_id , v );
		GL_TEST_ERROR("[in] vertex set")
	}
	void Attribute::set4(char *v)
	{
		glVertexAttrib4bv( m_attribute_id , (GLbyte*)v );
		GL_TEST_ERROR("[in] vertex set")
	}
	void Attribute::set4(unsigned char *v)
	{
		glVertexAttrib4ubv( m_attribute_id , v );
		GL_TEST_ERROR("[in] vertex set")
	}
	void Attribute::set4(unsigned short *v)
	{
		glVertexAttrib4usv( m_attribute_id , v );
		GL_TEST_ERROR("[in] vertex set")
	}
	void Attribute::set4(unsigned int *v)
	{
		glVertexAttrib4uiv( m_attribute_id , v );
		GL_TEST_ERROR("[in] vertex set")
	}

	// normalized
	void Attribute::setN(unsigned char v, unsigned char v2, unsigned char v3, unsigned char v4)
	{
		glVertexAttrib4Nub( m_attribute_id , v , v2 , v3 , v4 );
		GL_TEST_ERROR("[in] vertex set")
	}
	void Attribute::set4N(char *v)
	{
		glVertexAttrib4Nbv( m_attribute_id , (GLbyte*)v );
		GL_TEST_ERROR("[in] vertex set")
	}
	void Attribute::set4N(short *v)
	{
		glVertexAttrib4Nsv( m_attribute_id , v );
		GL_TEST_ERROR("[in] vertex set")
	}
	void Attribute::set4N(int *v)
	{
		glVertexAttrib4Niv( m_attribute_id , v );
		GL_TEST_ERROR("[in] vertex set")
	}
	void Attribute::set4N(unsigned char *v)
	{
		glVertexAttrib4Nubv( m_attribute_id , v );
		GL_TEST_ERROR("[in] vertex set")
	}
	void Attribute::set4N(unsigned short *v)
	{
		glVertexAttrib4Nusv( m_attribute_id , v );
		GL_TEST_ERROR("[in] vertex set")
	}
	void Attribute::set4N(unsigned int *v)
	{
		glVertexAttrib4Nuiv( m_attribute_id , v );
		GL_TEST_ERROR("[in] vertex set")
	}
}
