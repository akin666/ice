/*
 * UIButton.cpp
 *
 *  Created on: 23.7.2011
 *      Author: akin
 */

#include "uibutton.h"
#include <glm/transform>

namespace ice
{
	UIButton::UIButton()
	{
	}

	UIButton::~UIButton()
	{
	}

	void UIButton::initialize( Texture *on , Texture *off )
	{
		active.texture = on;
		inactive.texture = off;

		SimpleMesh::setPlane( active , active.texture->getDimension().x , active.texture->getDimension().y , active.texture );
		SimpleMesh::setPlane( inactive , inactive.texture->getDimension().x , inactive.texture->getDimension().y , inactive.texture );

		dimension = inactive.texture->getDimension();
	}

	void UIButton::render( glm::vec2& pos )
	{
		if( !visible )
		{
			return;
		}

		tmp = glm::translate( glm::mat4(1.0f), glm::vec3( pos.x+position.x , pos.y + position.y , 0.0f ) );

		if( selected == UIActive )
		{
			active.draw( tmp );
		}
		else
		{
			inactive.draw( tmp );
		}
	}
	bool UIButton::handleClickEvent( glm::vec2& pos , const Mouse& mouse , const unsigned int button , const float state )
	{
		if( !visible )
		{
			return false;
		}

		const glm::vec2 mdiff = mouse.getPointer() - (pos + position);
		if( state < 0.8f && ( selected == UIActive ) )
		{
			executeListenerEvent( UIClickRelease );

			if( mdiff.x < dimension.x && // X Right
				mdiff.y < dimension.y  &&// Y Top
				mdiff.x > 0.0f && // X Left
				mdiff.y > 0.0f ) // Y Bottom
			{
				selected = UIHover;
			}
			else
			{
				selected = UINone;
				executeListenerEvent( UIHoverOut );
			}
			dimension = active.texture->getDimension();

			return true;
		}

		if( mdiff.x < dimension.x && // X Right
			mdiff.y < dimension.y  &&// Y Top
			mdiff.x > 0.0f && // X Left
			mdiff.y > 0.0f ) // Y Bottom
		{
			if( state > 0.2f )
			{
				selected = UIActive;
				dimension = inactive.texture->getDimension();

				executeListenerEvent( UIClick );
				return true;
			}
		}

		return false;
	}

	bool UIButton::handleMoveEvent( glm::vec2& pos , const Mouse& mouse )
	{
		if( !visible )
		{
			return false;
		}

		if( selected == UINone )
		{
			const glm::vec2 mdiff = mouse.getPointer() - (pos + position);
			if( mdiff.x < dimension.x && // X Right
				mdiff.y < dimension.y  &&// Y Top
				mdiff.x > 0.0f && // X Left
				mdiff.y > 0.0f ) // Y Bottom
			{
				selected = UIHover;
				executeListenerEvent( UIHoverIn );
				return true;
			}
		}
		else if( selected == UIHover )
		{
			const glm::vec2 mdiff = mouse.getPointer() - (pos + position);
			if( !( mdiff.x < dimension.x && // X Right
				mdiff.y < dimension.y  &&// Y Top
				mdiff.x > 0.0f && // X Left
				mdiff.y > 0.0f ) ) // Y Bottom
			{
				selected = UINone;
				executeListenerEvent( UIHoverOut );
				return true;
			}
		}

		return false;
	}

	void UIButton::setShader( ShaderProgram *val )
	{
		active.setShader( val );
		inactive.setShader( val );

		shader = val;
	}
} /* namespace ice */
