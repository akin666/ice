/*
 * uiimage.h
 *
 *  Created on: 23.7.2011
 *      Author: akin
 */

#ifndef UIIMAGE_H_
#define UIIMAGE_H_

#include "uicomponent.h"
#include <graphics/texture/gtexture.h>
#include <graphics/mesh/simplemesh.h>

namespace ice
{
	class UIImage : public UIComponent
	{
	protected:
		SimpleMesh mesh;
		glm::mat4x4 tmp;
	public:
		UIImage();
		virtual ~UIImage();

		void initialize( Texture *texture );

		virtual void render( glm::vec2& pos );

		virtual bool handleClickEvent( glm::vec2& pos , const Mouse& mouse , const unsigned int button , const float state );
		virtual bool handleMoveEvent( glm::vec2& pos , const Mouse& mouse );

		virtual void setShader( ShaderProgram *val );
	};
} /* namespace ice */
#endif /* UIIMAGE_H_ */
