/*
 * glyph.cpp
 *
 *  Created on: 13.6.2011
 *      Author: akin
 */

#include "glyph.h"
#include <iostream>
#include <cstring>

namespace ice
{
	Glyph::Glyph()
	: code(0),
	  empty( true ),
	  kernings(NULL),
	  kerningCount(0)
	{
	}

	Glyph::Glyph( const Glyph& other )
	{
		texLocation = other.texLocation;
		texDimensions = other.texDimensions;
		advance = other.advance;
		offset = other.offset;
		size = other.size;

		code = other.code;
		empty = other.empty;

		kerningCount = other.kerningCount;
		if( kerningCount > 0 )
		{
			kernings = new Kerning[other.kerningCount];
			::memcpy( kernings , other.kernings , kerningCount * sizeof(Kerning) );
		}
		else
		{
			kernings = NULL;
		}
	}

	Glyph::~Glyph()
	{
		if( kernings != NULL )
		{
			delete[] kernings;
			kernings = NULL;
			kerningCount = 0;
		}
	}

	UNICODE Glyph::getUnicode() const
	{
		return code;
	}

	void Glyph::setTextureLocation( const glm::ivec2& val )
	{
		texLocation = val;
	}

	void Glyph::setTextureSize( const glm::ivec2& val )
	{
		texDimensions = val;
	}

	void Glyph::setAdvance( const glm::vec2& val )
	{
		advance = val;
	}

	void Glyph::setOffset( const glm::vec2& val )
	{
		offset = val;
	}

	void Glyph::setSize( const glm::vec2& val )
	{
		size = val;
	}

	void Glyph::setUnicode( const UNICODE val )
	{
		code = val;
	}

	glm::vec2& Glyph::getAdvance()
	{
		return advance;
	}

	glm::vec2& Glyph::getOffset()
	{
		return offset;
	}

	glm::vec2& Glyph::getSize()
	{
		return size;
	}

	glm::ivec2& Glyph::getTextureLocation()
	{
		return texLocation;
	}

	glm::ivec2& Glyph::getTextureDimensions()
	{
		return texDimensions;
	}

	bool Glyph::isEmpty() const
	{
		return empty;
	}

	void Glyph::setEmpty( const bool val )
	{
		empty = val;
	}

	void Glyph::print()
	{
		std::cout << "------------------" << std::endl;
		std::cout << "Font Texture:" << std::endl;
		std::cout << " Location: " << texLocation.x << "," << texLocation.y << std::endl;
		std::cout << " Dimensions: " << texDimensions.x << "," << texDimensions.y << std::endl;
		std::cout << "Font Values:" << std::endl;
		std::cout << " Code: " << code << std::endl;
		std::cout << " Empty: " << (empty?"yes":"no") << std::endl;
		std::cout << " Advance: " << advance.x << "," << advance.y << std::endl;
		std::cout << " Offset: " << offset.x << "," << offset.y << std::endl;
		std::cout << " Size: " << size.x << "," << size.y << std::endl;
	}
}

