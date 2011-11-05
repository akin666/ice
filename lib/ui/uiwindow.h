/*
 * uiwindow.h
 *
 *  Created on: 24.7.2011
 *      Author: akin
 */

#ifndef UIWINDOW_H_
#define UIWINDOW_H_

#include "uiarea.h"
#include "uiparent.h"

namespace ice
{
	class UIWindow : public UIComponent , public UIParent
	{
	protected:
		glm::mat4x4 tmp;
		UIArea container;
		SimpleMesh mesh;
	public:
		UIWindow();
		virtual ~UIWindow();

		void refresh();

		UIContainer& getContainer();

		void initialize( Texture *texture , Texture *texture2 );

		virtual void render( glm::vec2& pos );

		virtual bool handleClickEvent( glm::vec2& pos , const Mouse& mouse , const unsigned int button , const float state );
		virtual bool handleMoveEvent( glm::vec2& pos , const Mouse& mouse );
		virtual void setVisible( bool state );

		virtual void addChild( UIComponent *child );
		virtual void removeChild( UIComponent *child );
		virtual void clearChilds();

		virtual void setShader( ShaderProgram *val );
	};
} /* namespace ice */
#endif /* UIWINDOW_H_ */
