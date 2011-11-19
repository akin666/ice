/*
 * texturefont.h
 *
 *  Created on: 4.8.2011
 *      Author: akin
 */

#ifndef FONT_H_
#define FONT_H_

#include <graphics/texture/gtextureatlas.h>
#include <graphics/texture/texture.h>
#include "glyph.h"
#include <map>
#include <system/common>
#include <dio/dio>

#define FL_LINE_FEED 10
#define FL_CARRIAGE_RETURN 13
#define FL_HORIZONTAL_TAB 9

namespace ice
{
	class Font
	{
	protected:
		GTextureAtlas atlas;
		glm::mat4x4 textureMatrix;

		unsigned char *filedata;
		void *data;

		std::map< UNICODE , Glyph > glyphs;

		bool loadSingleGlyph( UNICODE code );
		void updateMatrix();

		float size;
		float border;
		float gamma;
	public:
		Font();
		virtual ~Font();

		bool initialize( DIO& dio );
		bool initialize( const std::string filename );

		void cacheGlyphs( std::string utf8text );

		float getSize() const;

		bool load( const UNICODE glyph );
		bool load( const std::vector<UNICODE>& data );

		std::map< UNICODE, Glyph >& getGlyphs();

		void bind();
		GTexture& getTexture();
		glm::mat4x4& getTextureMatrix();
	};
} /* namespace ice */
#endif /* FONT_H_ */
