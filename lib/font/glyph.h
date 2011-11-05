/*
 * glyph.h
 *
 *  Created on: 13.6.2011
 *      Author: akin
 */

#ifndef GLYPH_H_
#define GLYPH_H_

#include <glm/glm>
#include "../../datatypes/common.h"
#include <vector>

namespace ice
{
	class Kerning
	{
	public:
		UNICODE code;
		float value;
	};

	class Glyph
	{
	protected:
		glm::ivec2 texLocation;
		glm::ivec2 texDimensions;

		// Next values are normalized to the FONT size.
		glm::vec2 advance;
		glm::vec2 offset;
		glm::vec2 size;

		UNICODE code;
		bool empty;

		Kerning *kernings;
		int kerningCount;
	public:
		Glyph();
		Glyph( const Glyph& other );

		virtual ~Glyph();

		UNICODE getUnicode() const;
		void setUnicode( const UNICODE val );
		void setTextureLocation( const glm::ivec2& val );
		void setTextureSize( const glm::ivec2& val );

		void setAdvance( const glm::vec2& val );
		void setOffset( const glm::vec2& val );
		void setSize( const glm::vec2& val );

		glm::vec2& getAdvance();
		glm::vec2& getOffset();
		glm::vec2& getSize();

		glm::ivec2& getTextureLocation();
		glm::ivec2& getTextureDimensions();

		bool isEmpty() const;
		void setEmpty( const bool val );

		void print();
	};
}

#endif /* GLYPH_H_ */
