/*
 * mouse.h
 *
 *  Created on: 21.7.2011
 *      Author: akin
 */

#ifndef MOUSE_H_
#define MOUSE_H_

#include <glm/glm>
#include <graphics/mesh/simplemesh.h>

namespace ice
{
	class Mouse
	{
	protected:
		glm::mat4x4 modelview;
		bool enabled;

		glm::ivec2 dimensions;

		SimpleMesh mesh;
	public:
		Mouse();
		virtual ~Mouse();

		void initialize( Texture *texture );

		void move( float x , float y );

		float getX() const;
		float getY() const;
		glm::vec2 getPosition() const;

		float getPointerX() const;
		float getPointerY() const;
		glm::vec2 getPointer() const;


		void setPosition( float x , float y );

		void setEnabled( bool val );
		bool isEnabled() const;

		void render();

		void setShader( ShaderProgram *val );
	};
}

#endif /* MOUSE_H_ */
