/*
 * viewcontainer.h
 *
 *  Created on: 22.7.2011
 *      Author: akin
 */

#ifndef VIEWCONTAINER_H_
#define VIEWCONTAINER_H_

#include "uicomponent.h"
#include <list>
#include "uiparent.h"

namespace ice
{
	class UIContainer : public UIComponent , public UIParent
	{
	protected:
		std::list< UIComponent *> childs;

		bool letChildHandleClickEvent( glm::vec2& pos , const Mouse& mouse , const unsigned int button , const float state );
		bool letChildHandleMoveEvent( glm::vec2& pos , const Mouse& mouse );
		void letChildRender( glm::vec2& pos );
	public:
		UIContainer();
		virtual ~UIContainer();

		void setFocus( UIComponent *child );

		virtual void render( glm::vec2& pos );

		virtual bool handleClickEvent( glm::vec2& pos , const Mouse& mouse , const unsigned int button , const float state );
		virtual bool handleMoveEvent( glm::vec2& pos , const Mouse& mouse );
		virtual void setVisible( bool state );

		virtual void addChild( UIComponent *child );
		virtual void removeChild( UIComponent *child );
		virtual void clearChilds();

		virtual void setShader( ShaderProgram *val );
	};
}

#endif /* VIEWCONTAINER_H_ */
