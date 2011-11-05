/*
 * texturegroup.h
 *
 *  Created on: 25.7.2011
 *      Author: akin
 */

#ifndef TEXTUREGROUP_H_
#define TEXTUREGROUP_H_

#include <vector>
#include "gtextureatlas.h"
#include "texture.h"

#define TG_DEFAULT_TEXTURE_SIZE 2048
#define TG_DEFAULT_PAD 1

namespace ice
{
	class TextureGroup
	{
	protected:
		std::vector<GTextureAtlas*> atlases;
		glm::ivec2 max;
		int pad;
		Color<float>::Mode channels;
		bool initialized;
	public:
		TextureGroup();
		virtual ~TextureGroup();

		bool initialize( const int maxwidth = TG_DEFAULT_TEXTURE_SIZE , const int maxheight = TG_DEFAULT_TEXTURE_SIZE , const int padding = TG_DEFAULT_PAD , const Color<float>::Mode mode = Color<float>::RGBA );
		bool initialize( const glm::ivec2& maxsize , const int padding = TG_DEFAULT_PAD , const Color<float>::Mode mode = Color<float>::RGBA );

		bool request( Texture& texture );
	};
} /* namespace ice */
#endif /* TEXTUREGROUP_H_ */
