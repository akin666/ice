/*
 * text.cpp
 *
 *  Created on: 31.7.2011
 *      Author: akin
 */

#include "text.h"
#include "textgenerator.h"
#include <sys/utf8decoder.h>

namespace ice
{
	Text::Text()
	{
	}

	Text::~Text()
	{
	}

	TextFormat& Text::getFormat()
	{
		return format;
	}

	void Text::setFormat( const TextFormat& val )
	{
		format = val;
	}

	void Text::setUTF8( std::string val )
	{
		if( val == "" )
		{
			text.clear();
		}

		UTF8Decoder decoder;
		if( decoder.init( val ) )
		{
			decoder.decodeTo( text );
		}
	}

	void Text::setText( std::vector<UNICODE> val )
	{
		text = val;
	}

	std::vector<UNICODE>& Text::getText()
	{
		return text;
	}

	bool Text::generate()
	{
		return TextGenerator::create( text , format , mesh );
	}

	TextMesh& Text::getMesh()
	{
		return mesh;
	}

	void Text::setShader( ShaderProgram *val )
	{
		mesh.setShader( val );
	}
} /* namespace ice */
