/*
 * uiarea.cpp
 *
 *  Created on: 23.7.2011
 *      Author: akin
 */

#include "uiarea.h"
#include <iostream>
#include <glm/transform>

namespace ice
{
	UIArea::UIArea()
	{
	}

	UIArea::~UIArea()
	{
	}

	void UIArea::initialize( Texture *texture )
	{
		if( texture == NULL )
		{
			std::cout << "UIArea tried to set null texture" << std::endl;
			return;
		}
		mesh.texture = texture;
		dimension = texture->getDimension();
		SimpleMesh::setPlane( mesh , texture->getDimension().x , texture->getDimension().y , texture );
	}

	void UIArea::refresh()
	{
		SimpleMesh::setPlane( mesh , getDimension().x , getDimension().y , mesh.texture );
	}

	void UIArea::render( glm::vec2& pos )
	{
		if( !visible )
		{
			return;
		}

		if( mesh.texture != NULL )
		{
			tmp = glm::translate( glm::mat4(1.0f), glm::vec3( pos.x+position.x , pos.y + position.y , 0.0f ) );

			//tmp.identity();
			//tmp.translate( pos.x + position.x , pos.y + position.y , 0.0f );
			mesh.draw( tmp );
		}
		letChildRender( pos );
	}

	bool UIArea::handleClickEvent( glm::vec2& pos , const Mouse& mouse , const unsigned int button , const float state )
	{
		if( !visible )
		{
			return false;
		}

		return letChildHandleClickEvent( pos , mouse , button , state );
	}

	bool UIArea::handleMoveEvent( glm::vec2& pos , const Mouse& mouse )
	{
		if( !visible )
		{
			return false;
		}

		return letChildHandleMoveEvent( pos , mouse );
	}

	void UIArea::setShader( ShaderProgram *val )
	{
		for( std::list< UIComponent *>::iterator iter = childs.begin() ; iter != childs.end() ; ++iter )
		{
			(*iter)->setShader( val );
		}
		mesh.setShader( val );
		shader = val;
	}
} /* namespace ice */
