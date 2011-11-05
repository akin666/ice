/*
 * UIButton.h
 *
 *  Created on: 23.7.2011
 *      Author: akin
 */

#ifndef UIBUTTON_H_
#define UIBUTTON_H_

#include "uicomponent.h"
#include "../graphics/simplemesh.h"

namespace ice
{
	class UIButton : public UIComponent
	{
	protected:
		SimpleMesh active;
		SimpleMesh inactive;
		glm::mat4x4 tmp;
	public:
		UIButton();
		virtual ~UIButton();

		void initialize( Texture *on , Texture *off );

		virtual void render( glm::vec2& pos );

		virtual bool handleClickEvent( glm::vec2& pos , const Mouse& mouse , const unsigned int button , const float state );
		virtual bool handleMoveEvent( glm::vec2& pos , const Mouse& mouse );

		virtual void setShader( ShaderProgram *val );
	};
} /* namespace ice */
#endif /* UIBUTTON_H_ */
