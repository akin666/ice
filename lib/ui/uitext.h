/*
 * uitext.h
 *
 *  Created on: 24.7.2011
 *      Author: akin
 */

#ifndef UILABEL_H_
#define UILABEL_H_

#include "uicomponent.h"
#include <font/font.h>
#include <text/text.h>
#include <glm/glm>

namespace ice
{
	class UIText : public UIComponent
	{
	protected:
		Text text;
		glm::mat4x4 tmp;
	public:
		UIText();
		virtual ~UIText();

		void setUTF8( const std::string txt );
		void setText( const std::vector<UNICODE>& txt );
		void setFont( const std::string font );
		void setFontSize( const float height );
		void setFontColor( const glm::vec4& color );

		void apply();

		virtual void render( glm::vec2& pos );

		virtual bool handleClickEvent( glm::vec2& pos , const Mouse& mouse , const unsigned int button , const float state );
		virtual bool handleMoveEvent( glm::vec2& pos , const Mouse& mouse );

		virtual void setShader( ShaderProgram *val );
	};
} /* namespace ice */
#endif /* UILABEL_H_ */
