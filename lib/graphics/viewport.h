/*
 * viewport.h
 *
 *  Created on: 5.8.2011
 *      Author: akin
 */

#ifndef VIEWPORT_H_
#define VIEWPORT_H_

#include <glm/glm>

namespace ice
{
	class Viewport
	{
	protected:
		glm::mat4x4 projection;
		glm::mat4x4 model;
	public:
		Viewport();
		virtual ~Viewport();

		glm::mat4x4& getProjectionMatrix();
		glm::mat4x4& getModelMatrix();

		// Lenses:
		void setOrtho( float width , float height , float near , float far );
		void setFrustum( float left , float right , float bottom , float top , float near , float far );
	};
} /* namespace ice */
#endif /* VIEWPORT_H_ */
