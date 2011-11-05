/*
 * uiarea.h
 *
 *  Created on: 23.7.2011
 *      Author: akin
 */

#ifndef UIAREA_H_
#define UIAREA_H_

#include "uicontainer.h"
#include <graphics/simplemesh.h>

namespace ice
{
	class UIArea : public UIContainer
	{
	protected:
		glm::mat4x4 tmp;
		SimpleMesh mesh;
	public:
		UIArea();
		virtual ~UIArea();

		void refresh();

		void initialize( Texture *texture );

		virtual void render( glm::vec2& pos );

		virtual bool handleClickEvent( glm::vec2& pos , const Mouse& mouse , const unsigned int button , const float state );

		virtual bool handleMoveEvent( glm::vec2& pos , const Mouse& mouse );

		virtual void setShader( ShaderProgram *val );
	};
} /* namespace ice */
#endif /* UIAREA_H_ */
