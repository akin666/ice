/*
 * uiimage.cpp
 *
 *  Created on: 23.7.2011
 *      Author: akin
 */

#include "uiimage.h"
#include <iostream>
#include <glm/transform>

namespace ice
{
	UIImage::UIImage()
	{
	}

	UIImage::~UIImage()
	{
	}

	void UIImage::initialize( Texture *texture )
	{
		if( texture == NULL )
		{
			std::cout << "UIImage tried to set null texture" << std::endl;
			return;
		}
		mesh.texture = texture;
		dimension = texture->getDimension();
		SimpleMesh::setPlane( mesh , texture->getDimension().x , texture->getDimension().y , texture );
	}

	void UIImage::render( glm::vec2& pos )
	{
		if( !visible )
		{
			return;
		}

		tmp = glm::translate( glm::mat4(1.0f), glm::vec3( pos.x+position.x , pos.y + position.y , 0.0f ) );

		mesh.draw( tmp );

#ifdef UI_DEBUG_HOVER
		mesh.color.x = 1.0f;
		mesh.color.y = 1.0f;
#endif
	}
	bool UIImage::handleClickEvent( glm::vec2& pos , const Mouse& mouse , const unsigned int button , const float state )
	{
		if( !visible )
		{
			return false;
		}

		if( selected != UINone && state < 0.8f )
		{
			selected = UINone;
			return true;
		}

		const glm::vec2 mdiff = mouse.getPointer() - (pos + position);
		if( mdiff.x < dimension.x && // X Right
			mdiff.y < dimension.y  &&// Y Top
			mdiff.x > 0.0f && // X Left
			mdiff.y > 0.0f ) // Y Bottom
		{
			if( state > 0.2f )
			{
				selected = UIDrag;

				dislocation = mouse.getPointer() - position;
			}

			return true;
		}

		return false;
	}

	bool UIImage::handleMoveEvent( glm::vec2& pos , const Mouse& mouse )
	{
		if( !visible )
		{
			return false;
		}
#ifdef UI_DEBUG_HOVER
		const glm::vec2 mdiff = mouse.getPointer() - (pos + position);

		// Child did not handle it!
		if( mdiff.x < dimensions.x && // X Right
			mdiff.y < dimensions.y  &&// Y Top
			mdiff.x > 0.0f && // X Left
			mdiff.y > 0.0f ) // Y Bottom
		{
			mesh.color.x = 0.0f;
			mesh.color.y = 0.0f;
		}
#endif
		if( selected == UIDrag )
		{
			position = mouse.getPointer() - dislocation;
			return true;
		}
		return false;
	}

	void UIImage::setShader( ShaderProgram *val )
	{
		mesh.setShader( val );
		shader = val;
	}
} /* namespace ice */

