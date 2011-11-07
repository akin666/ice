/*
 * uitext.cpp
 *
 *  Created on: 24.7.2011
 *      Author: akin
 */

#include "uitext.h"
#include "../text/textgenerator.h"
#include <glm/transform>

namespace ice
{
	UIText::UIText()
	{
	}

	UIText::~UIText()
	{
	}

	void UIText::setUTF8( const std::string txt )
	{
		text.setUTF8( txt );
	}

	void UIText::setText( const std::vector<UNICODE>& txt )
	{
		text.setText( txt );
	}

	void UIText::setFont( const std::string font )
	{
		text.getFormat().setFont( font );
	}

	void UIText::setFontSize( const float height )
	{
		text.getFormat().setSize( height );
	}

	void UIText::setFontColor( const glm::vec4& color )
	{
		text.getFormat().setColor( color );
	}

	void UIText::apply()
	{
		text.generate();
	}

	void UIText::render( glm::vec2& pos )
	{
		tmp = glm::translate( glm::mat4(1.0f), glm::vec3( pos.x+position.x , pos.y + position.y , 0.0f ) );
		text.getMesh().draw( tmp );
	}

	bool UIText::handleClickEvent( glm::vec2& pos , const Mouse& mouse , const unsigned int button , const float state )
	{
		return false;
	}

	bool UIText::handleMoveEvent( glm::vec2& pos , const Mouse& mouse )
	{
		return false;
	}

	void UIText::setShader( ShaderProgram *val )
	{
		text.setShader( val );
		shader = val;
	}

} /* namespace ice */
