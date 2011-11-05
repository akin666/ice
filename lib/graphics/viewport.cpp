/*
 * viewport.cpp
 *
 *  Created on: 5.8.2011
 *      Author: akin
 */

#include "viewport.h"
#include <glm/transform>

namespace ice
{
	Viewport::Viewport()
	{
	}

	Viewport::~Viewport()
	{
	}

	glm::mat4x4& Viewport::getProjectionMatrix()
	{
		return projection;
	}

	glm::mat4x4& Viewport::getModelMatrix()
	{
		return model;
	}

	// Lenses:
	void Viewport::setOrtho( float width , float height , float near , float far )
	{
		projection = glm::ortho( 0.0f , width , height , 0.0f , near , far );
	}

	void Viewport::setFrustum( float left , float right , float bottom , float top , float near , float far )
	{
		projection = glm::frustum( left , right , bottom , top , near , far );
	}
} /* namespace ice */
