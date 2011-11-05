/*
 * uiframe.h
 *
 *  Created on: 22.7.2011
 *      Author: akin
 */

#ifndef UIFRAME_H_
#define UIFRAME_H_

#include <input/inputlistener.h>
#include "mouse.h"
#include "uicontainer.h"
#include "uiparent.h"
#include <graphics/shaderprogram.h>

namespace ice
{
	class UIFrame : public InputListener , public UIParent
	{
		// Statics:
	protected:
		static UIFrame *current;
	public:
		static bool hasCurrent();
		static UIFrame *getCurrent();
		static void setCurrent( UIFrame *frame );

		// Members
	protected:
		Mouse mouse;
		UIContainer container;
		glm::mat4x4 projection;
		glm::ivec2 dimensions;
		ShaderProgram *shader;
	public:
		UIFrame();
		virtual ~UIFrame();

		float getWidth() const;
		float getHeight() const;

		void setWidth( const float width );
		void setHeight( const float height );

		void setDimensions( const float width , const float height );

		void initialize();

		Mouse*getMouse();
		UIContainer& getContainer();
		glm::mat4x4& getProjection();

		virtual void render();

		virtual void handleMouseMove( const float x , const float y );
		virtual void handleMouseButton( const Button button , const float state );

		void setVisible( bool state );
		bool isVisible();

		virtual void addChild( UIComponent *child );
		virtual void removeChild( UIComponent *child );
		virtual void clearChilds();

		void setShader( ShaderProgram *val );
		ShaderProgram *getShader();
	};
} /* namespace ice */
#endif /* UIFRAME_H_ */
