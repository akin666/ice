/*
 * mouse.cpp
 *
 *  Created on: 21.7.2011
 *      Author: akin
 */

#include "mouse.h"
#include <iostream>
#include <glm/transform>

namespace ice
{
	Mouse::Mouse()
	: enabled( false )
	{
	}

	Mouse::~Mouse()
	{
	}

	void Mouse::initialize( Texture *texture )
	{
		if( texture == NULL )
		{
			std::cout << "Mouse::initialize NULL texture" << std::endl;
			return;
		}
		enabled = true;

		mesh.texture = texture;
		dimensions = texture->getDimension();

		SimpleMesh::setPlane( mesh , texture->getDimension().x , texture->getDimension().y , texture );
	}

	void Mouse::move( float x , float y )
	{
		modelview = glm::translate( modelview , glm::vec3(x , y , 0.0f) );
		//modelview.translate( x , y , 0.0f );
	}

	float Mouse::getX() const
	{
		glm::vec4 pos = modelview * glm::vec4(0.0f,0.0f,0.0f,0.0f);

		return pos.x;
		//return modelview.getX();
	}

	float Mouse::getY() const
	{
		glm::vec4 pos = modelview * glm::vec4(0.0f,0.0f,0.0f,0.0f);

		return pos.y;
		//return modelview.getY();
	}

	glm::vec2 Mouse::getPosition() const
	{
		glm::vec4 pos = modelview * glm::vec4(0.0f,0.0f,0.0f,0.0f);

		return glm::vec2( pos.x , pos.y );
	}

	float Mouse::getPointerX() const
	{
		return getX();
	}

	float Mouse::getPointerY() const
	{
		return getY();
	}

	glm::vec2 Mouse::getPointer() const
	{
		glm::vec4 pos = modelview * glm::vec4(0.0f,0.0f,0.0f,0.0f);

		return glm::vec2( pos.x , pos.y );
	}

	void Mouse::setPosition( float x , float y )
	{
		modelview = glm::translate( glm::mat4(1.0f) , glm::vec3(x , y , 0.0f) );
		//modelview.identity();
		//modelview.translate( x , y , 0.0f );
	}

	void Mouse::setEnabled( bool val )
	{
		enabled = val;
	}

	bool Mouse::isEnabled() const
	{
		return enabled;
	}

	void Mouse::render()
	{
		if( enabled )
		{
			// render.
			mesh.draw( modelview );
		}
	}

	void Mouse::setShader( ShaderProgram *val )
	{
		mesh.setShader( val );
	}
}


