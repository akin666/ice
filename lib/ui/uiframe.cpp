 /*
 * uiframe.cpp
 *
 *  Created on: 22.7.2011
 *      Author: akin
 */

#include "uiframe.h"
#include <system/opengl>
#include <glm/transform>

#define MIN_DEPTH 0.0f
#define MAX_DEPTH 10.0f

namespace ice
{
	UIFrame::UIFrame()
	: shader( NULL )
	{
		dimensions.x = 400;
		dimensions.y = 300;

		container.setVisible( true );
	}

	UIFrame::~UIFrame()
	{
	}

	float UIFrame::getWidth() const
	{
		return dimensions.x;
	}

	float UIFrame::getHeight() const
	{
		return dimensions.y;
	}

	void UIFrame::setWidth( const float width )
	{
		dimensions.x = width;
	}

	void UIFrame::setHeight( const float height )
	{
		dimensions.y = height;
	}

	void UIFrame::setDimensions( const float width , const float height )
	{
		dimensions.x = width;
		dimensions.y = height;
	}

	void UIFrame::initialize()
	{
		projection = glm::ortho(
				0.0f ,
				(float)dimensions.x ,
				(float)dimensions.y ,
				0.0f ,
				MIN_DEPTH,
				MAX_DEPTH
				);


//		projection.ortho(
//				0,
//				dimensions.x ,
//				dimensions.y ,
//				0,
//				MIN_DEPTH,
//				MAX_DEPTH
//		);

		mouse.setPosition( dimensions.x / 2.0f , dimensions.y / 2.0f );
	}

	void UIFrame::setVisible( bool state )
	{
		container.setVisible( state );
	}

	bool UIFrame::isVisible()
	{
		return container.isVisible();
	}

	Mouse *UIFrame::getMouse()
	{
		return &mouse;
	}

	UIContainer& UIFrame::getContainer()
	{
		return container;
	}

	glm::mat4x4& UIFrame::getProjection()
	{
		return projection;
	}

	void UIFrame::handleMouseMove( const float x , const float y )
	{
		const float futureX = mouse.getPointerX() + x;
		const float futureY = mouse.getPointerY() + y;

		if( futureX > dimensions.x ||
			futureX < 0.0f ||
			futureY > dimensions.y ||
			futureY < 0.0f )
		{
			float nx = x;
			float ny = y;

			if( futureX > dimensions.x )
			{
				nx = dimensions.x - mouse.getPointerX();
			}
			else if( futureX < 0.0f )
			{
				nx = -mouse.getPointerX();
			}

			if( futureY > dimensions.y )
			{
				ny = dimensions.y - mouse.getPointerY();
			}
			else if( futureY < 0.0f )
			{
				ny = -mouse.getPointerY();
			}

			glm::vec2 pos;
			mouse.move( nx , ny );
			container.handleMoveEvent( pos , mouse );

			// Off the screen.
			return;
		}

		glm::vec2 pos;
		mouse.move( x , y );
		container.handleMoveEvent( pos , mouse );
	}

	void UIFrame::handleMouseButton( const Button button , const float state )
	{
		glm::vec2 pos;
		container.handleClickEvent( pos , mouse , button , state );
	}

	void UIFrame::render()
	{
		glViewport( 0 , 0 , dimensions.x , dimensions.y );
		glDisable( GL_DEPTH_TEST );
//		glMatrixMode( GL_PROJECTION );
//		glLoadMatrixf( projection.get() );
//		glMatrixMode( GL_MODELVIEW );

		glm::vec2 pos;

		container.render( pos );

		mouse.render();
	}

	void UIFrame::addChild( UIComponent *child )
	{
		container.addChild( child );
	}

	void UIFrame::removeChild( UIComponent *child )
	{
		container.removeChild( child );
	}

	void UIFrame::clearChilds()
	{
		container.clearChilds();
	}

	void UIFrame::setShader( ShaderProgram *val )
	{
		shader = val;

		if( shader != NULL )
		{
			shader->bind();
			Uniform *lense = shader->getUniform( "lense" );

			lense->set( projection );
		}

		mouse.setShader( shader );
		container.setShader( shader );
	}

	ShaderProgram *UIFrame::getShader()
	{
		return shader;
	}
} /* namespace ice */
