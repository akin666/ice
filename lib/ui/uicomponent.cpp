/*
 * uiview.cpp
 *
 *  Created on: 21.7.2011
 *      Author: akin
 */

#include "uicomponent.h"
#include <iostream>

namespace ice
{
	UIComponent::UIComponent()
	: shader(NULL),
	  parent(NULL),
	  selected(UINone),
	  visible( false )
	{
		for( int i = UIListenerCount-1 ; i >= 0 ; --i )
		{
			eventScriptActive[ i ] = false;
		}
	}

	UIComponent::~UIComponent()
	{
		clearParent();
	}

	void UIComponent::setIdent( std::string val )
	{
		ident = val;
	}

	std::string UIComponent::getIdent()
	{
		return ident;
	}

	glm::vec2& UIComponent::getPosition()
	{
		return position;
	}

	glm::vec2& UIComponent::getDimension()
	{
		return dimension;
	}

	float UIComponent::getWidth() const
	{
		return dimension.x;
	}

	float UIComponent::getHeight() const
	{
		return dimension.y;
	}

	void UIComponent::setWidth( float width )
	{
		dimension.x = width;
	}

	void UIComponent::setHeight( float height )
	{
		dimension.y = height;
	}

	float UIComponent::getX() const
	{
		return position.x;
	}

	float UIComponent::getY() const
	{
		return position.x;
	}

	void UIComponent::setX( float x )
	{
		position.x = x;
	}

	void UIComponent::setY( float y )
	{
		position.y = y;
	}

	void UIComponent::setSize( float width , float height )
	{
		dimension.x = width;
		dimension.y = height;
	}

	void UIComponent::setPosition( float x , float y )
	{
		dimension.x = x;
		dimension.y = y;
	}

	void UIComponent::setVisible( bool state )
	{
		visible = state;
	}

	bool UIComponent::isVisible()
	{
		return visible;
	}

	UIListenerEvents UIComponent::translateListenerEvent( std::string eventName )
	{
		if( eventName == "onClick" )
		{
			return UIClick;
		}
		else if( eventName == "onClickRelease" )
		{
			return UIClickRelease;
		}
		else if( eventName == "onHoverIn" )
		{
			return UIHoverIn;
		}
		else if( eventName == "onHoverOut" )
		{
			return UIHoverOut;
		}
		else if( eventName == "onChange" )
		{
			return UIChange;
		}

		return UIListenerCount;
	}

	void UIComponent::setScript( std::string listener , std::string script )
	{
		const UIListenerEvents event = translateListenerEvent( listener );

		if( event < UIListenerCount )
		{
			if( script != "" )
			{
				eventScriptActive[ event ] = true;
			}
			eventScript[ event ] = script;
		}
	}

	void UIComponent::setScriptState(  std::string listener ,  bool state )
	{
		const UIListenerEvents event = translateListenerEvent( listener );

		if( event < UIListenerCount )
		{
			eventScriptActive[ event ] = state;
		}
	}

	std::string UIComponent::getScript( std::string listener )
	{
		const UIListenerEvents event = translateListenerEvent( listener );

		if( event < UIListenerCount )
		{
			return eventScript[ event ];
		}
		return "";
	}

	bool UIComponent::getScriptState(  std::string listener )
	{
		const UIListenerEvents event = translateListenerEvent( listener );

		if( event < UIListenerCount )
		{
			return eventScriptActive[ event ];
		}
		return false;
	}

	void UIComponent::executeListenerEvent( const UIListenerEvents& event )
	{
		if( event < UIListenerCount && eventScriptActive[ event ] )
		{
			// Execute eventscript
			std::cout << "Run " << eventScript[ event ] << std::endl;
		}
	}

	void UIComponent::setParent( UIParent *val )
	{
		parent = val;
	}

	bool UIComponent::hasParent()
	{
		return parent != NULL;
	}

	void UIComponent::clearParent()
	{
		if( hasParent() )
		{
			parent->removeChild( this );
			parent = NULL;
		}
	}

	void UIComponent::setShader( ShaderProgram *val )
	{
		shader = val;
	}

	ShaderProgram *UIComponent::getShader()
	{
		return shader;
	}
}



