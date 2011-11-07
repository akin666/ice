/*
 * textformat.cpp
 *
 *  Created on: 31.7.2011
 *      Author: akin
 */

#include "textformat.h"

#define DEFAULT_PIXEL_HEIGHT 16

namespace ice
{
	TextFormat::TextFormat()
	: pixelHeight( DEFAULT_PIXEL_HEIGHT ),
	  color( white ),
	  italic( false ),
	  bold( false )
	{
	}

	TextFormat::TextFormat( const TextFormat& other )
	: pixelHeight( other.pixelHeight ),
	  color( other.color),
	  italic( other.italic ),
	  bold( other.bold )
	{
	}

	TextFormat::~TextFormat()
	{
	}

	void TextFormat::setSize( const float height )
	{
		pixelHeight = height;
	}

	void TextFormat::setColor( const Color<float>& val )
	{
		color = val;
	}

	void TextFormat::setItalic( const bool val )
	{
		italic = val;
	}

	void TextFormat::setBold( const bool val )
	{
		bold = val;
	}

	float TextFormat::getSize() const
	{
		return pixelHeight;
	}

	Color<float> TextFormat::getColor() const
	{
		return color;
	}

	bool TextFormat::getItalic() const
	{
		return italic;
	}

	bool TextFormat::getBold() const
	{
		return bold;
	}

	void TextFormat::setFont( const std::string fontName )
	{
		font = fontName;
	}

	std::string TextFormat::getFontName() const
	{
		return font;
	}

} /* namespace ice */
