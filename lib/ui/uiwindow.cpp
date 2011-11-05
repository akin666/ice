/*
 * uiwindow.cpp
 *
 *  Created on: 24.7.2011
 *      Author: akin
 */

#include "uiwindow.h"

#define RESIZE_SQUARE_SIZE 20.0f
#define TOP_PADDING 30.0f
#define BOTTOM_PADDING RESIZE_SQUARE_SIZE
#define MIN_DIMENSION_X 100.0f
#define MIN_DIMENSION_Y 100.0f

#include <glm/transform>

namespace ice
{
	UIWindow::UIWindow()
	{
	}

	UIWindow::~UIWindow()
	{
	}

	UIContainer& UIWindow::getContainer()
	{
		return container;
	}

	void UIWindow::refresh()
	{
		SimpleMesh::setPlane( mesh , dimension.x , dimension.y , mesh.texture );

		// Container positioning.
		container.getDimension().x = getDimension().x;
		container.getDimension().y = getDimension().y - (TOP_PADDING + BOTTOM_PADDING);
		container.getPosition() = glm::vec2( 0 , TOP_PADDING );

		container.refresh();
	}

	void UIWindow::initialize( Texture *texture , Texture *texture2 )
	{
		if( texture == NULL )
		{
			std::cout << "UIWindow tried to set null texture" << std::endl;
			return;
		}
		mesh.texture = texture;
		dimension = texture->getDimension();

		SimpleMesh::setPlane( mesh , texture->getDimension().x , texture->getDimension().y , texture );

		container.initialize( texture2 );

		refresh();
	}

	void UIWindow::render( glm::vec2& pos )
	{
		if( !visible )
		{
			return;
		}

		pos += position;

		tmp = glm::translate( glm::mat4(1.0f), glm::vec3( pos.x , pos.y , 0.0f ) );
		mesh.draw( tmp );

		container.render( pos );
		pos -= position;
	}

	bool UIWindow::handleClickEvent( glm::vec2& pos , const Mouse& mouse , const unsigned int button , const float state )
	{
		if( !visible )
		{
			return false;
		}

		pos += position;
		bool childHandled = container.handleClickEvent( pos , mouse , button , state );
		pos -= position;

		// Child did not handle it!
		if( !childHandled )
		{
			if( selected != UINone && state < 0.8f )
			{
				selected = UINone;
				return true;
			}

			const glm::vec2 mdiff = mouse.getPointer() - (pos + position);

			if( state > 0.2f )
			{
				if( mdiff.x < dimension.x &&
					mdiff.y < dimension.y  &&
					mdiff.x > 0.0f &&
					mdiff.y > 0.0f )
				{
					// Inside the area

					// Is inside lower right corner, for resize?
					// If not, then its a move.
					if(	mdiff.x > dimension.x - RESIZE_SQUARE_SIZE &&
						mdiff.y > dimension.y - RESIZE_SQUARE_SIZE )
					{
						selected = UIResize;
						dislocation = mouse.getPointer() - dimension;

						return true;
					}
					else
					{
						selected = UIDrag;
						dislocation = mouse.getPointer() - position;

						return true;
					}
				}
			}
		}
		return childHandled;
	}

	bool UIWindow::handleMoveEvent( glm::vec2& pos , const Mouse& mouse )
	{
		if( !visible )
		{
			return false;
		}

		switch( selected )
		{
		case UIResize :
			{
				dimension = mouse.getPointer() - dislocation;

				if( dimension.x < MIN_DIMENSION_X )
				{
					dimension.x = MIN_DIMENSION_X;
				}
				if( dimension.y < MIN_DIMENSION_Y )
				{
					dimension.y = MIN_DIMENSION_Y;
				}

				refresh();
				return true;
			}
		case UIDrag :
			{
				position = mouse.getPointer() - dislocation;
				return true;
			}
		default:
			break;
		}

		pos += position;
		bool childHandled = container.handleMoveEvent( pos , mouse );
		pos -= position;

		return childHandled;
	}

	void UIWindow::setVisible( bool state )
	{
		container.setVisible( state );
		visible = state;
	}

	void UIWindow::addChild( UIComponent *child )
	{
		container.addChild( child );
	}

	void UIWindow::removeChild( UIComponent *child )
	{
		container.removeChild( child );
	}

	void UIWindow::clearChilds()
	{
		container.clearChilds();
	}

	void UIWindow::setShader( ShaderProgram *val )
	{
		mesh.setShader( val );

		container.setShader( val );

		shader = val;
	}
} /* namespace ice */
