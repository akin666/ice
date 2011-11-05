/*
 * uicomponent.h
 *
 *  Created on: 21.7.2011
 *      Author: akin
 */

#ifndef UIVIEW_H_
#define UIVIEW_H_

#include <glm/glm>
#include "uieventhandler.h"
#include "uiparent.h"
#include <graphics/shaderprogram.h>

#define UI_DEBUG_HOVER
#undef UI_DEBUG_HOVER

namespace ice
{
	enum UISelectState
	{
		UIActive,
		UIDrag,
		UIResize,
		UIHover,
		UINone,
	};

	enum UIListenerEvents
	{
		UIClick,
		UIClickRelease,
		UIHoverIn,
		UIHoverOut,
		UIChange,
		UIListenerCount,
	};

	class UIComponent : public UIEventHandler
	{
	protected:
		std::string ident;

		ShaderProgram *shader;
		UIParent *parent;
		UISelectState selected;
		bool visible;

		bool eventScriptActive[ UIListenerCount ];
		std::string eventScript[ UIListenerCount ];

		glm::vec2 position;
		glm::vec2 dimension;
		glm::vec2 dislocation;

		static UIListenerEvents translateListenerEvent( const std::string eventName );
		void executeListenerEvent( const UIListenerEvents& event );
	public:
		UIComponent();
		virtual ~UIComponent();

		void setIdent( std::string val );
		std::string getIdent();

		virtual void setVisible( bool state );
		bool isVisible();

		glm::vec2& getPosition();
		glm::vec2& getDimension();

		void setWidth( float width );
		void setHeight( float height );

		void setSize( float width , float height );

		float getWidth() const;
		float getHeight() const;

		void setX( float x );
		void setY( float y );

		float getX() const;
		float getY() const;

		void setPosition( float x , float y );

		virtual void render( glm::vec2& pos ) = 0;

		void setScript( std::string listener , std::string script );
		void setScriptState(  std::string listener ,  bool state );

		std::string getScript( std::string listener );
		bool getScriptState( std::string listener );

		virtual bool handleClickEvent( glm::vec2& pos , const Mouse& mouse , const unsigned int button , const float state ) = 0;
		virtual bool handleMoveEvent( glm::vec2& pos , const Mouse& mouse ) = 0;

		void setParent( UIParent *val );
		bool hasParent();
		void clearParent();

		virtual void setShader( ShaderProgram *val );
		ShaderProgram *getShader();
	};
}

#endif /* UIVIEW_H_ */
