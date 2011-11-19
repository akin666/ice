/*
 * Texture.cpp
 *
 *  Created on: 25.7.2011
 *      Author: akin
 */

#include "texture.h"

namespace ice
{
	Texture::Texture()
	: parent(NULL)
	{
	}

	Texture::Texture( const Texture& other )
	: parent( other.parent ),
	  pixelDimension( other.pixelDimension ),
	  pixelPosition( other.pixelPosition)
	{
	}

	Texture::~Texture()
	{
	}

	int Texture::getWidth() const
	{
		return pixelDimension.x;
	}

	int Texture::getHeight() const
	{
		return pixelDimension.y;
	}

	glm::ivec2& Texture::getDimension()
	{
		return pixelDimension;
	}

	glm::ivec2& Texture::getPosition()
	{
		return pixelPosition;
	}

	glm::vec2 Texture::getMax()
	{
		glm::vec2 max( pixelPosition + pixelDimension );
		glm::vec2 div( parent->getDimension() );

		return max / div;
	}

	glm::vec2 Texture::getMin()
	{
		glm::vec2 min( pixelPosition );
		glm::vec2 div( parent->getDimension() );

		return min / div;
	}

	GTexture *Texture::getG()
	{
		return parent;
	}

	void Texture::bind()
	{
		parent->bind();
	}

	void Texture::release()
	{
		parent->release();
	}

	void Texture::setTexture( GTexture *texture )
	{
		parent = texture;
	}

	unsigned int Texture::getId() const
	{
		if( parent == NULL ) return 0;

		return parent->getTextureId();
	}
} /* namespace ice */
