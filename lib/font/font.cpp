/*
 * font.cpp
 *
 *  Created on: 4.8.2011
 *      Author: akin
 *
 *  parts taken from freetype-gl
 *  those parts are under BSD, but, others ARE NOT.
 */

#include "font.h"
#include <iostream>
#include "../../dio/filedio.h"
#include <iterator>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "edtaa3func.h"

#include "../../sys/utf8tools.h"
#include <glm/transform>

#define DEFAULT_TEXTURE_SIZE 64
#define DEFAULT_TEXTURE_PADDING 1

namespace ice
{
	class FTSingleton {
	private:
		static FTSingleton *singleton;
	public:
		FTSingleton(){}
		virtual ~FTSingleton(){}

		static FTSingleton &get()
		{
			if( singleton == NULL )
			{
				singleton = new FTSingleton;

				FT_Error error = FT_Init_FreeType( &(singleton->library) );
				if ( error )
				{
					std::cout << "FT_Error Failed to initialize FTLibrary " << std::endl;
					::exit( -1 );
				}
			}
			return *singleton;
		}

		FT_Library library;
	};
	FTSingleton *FTSingleton::singleton = NULL;

	class FTFontData
	{
	public:
		FT_Error      error;
		FT_Face       face;

		~FTFontData()
		{
			FT_Done_Face( face );
		}
	};

	Font::Font()
	: filedata(NULL)
	{
		data = new FTFontData;
	}

	Font::~Font()
	{
		if( filedata != NULL )
		{
			delete[] filedata;
			filedata = NULL;
		}
		if( data != NULL )
		{
			delete (FTFontData*)data;
			data = NULL;
		}
	}

	void Font::updateMatrix()
	{
		textureMatrix = glm::scale( glm::mat4(1.0f) , glm::vec3( 1.0f / (float)atlas.getDimension().x , 1.0f / (float)atlas.getDimension().y , 1.0f ) );
	}

	bool Font::initialize( DIO& dio )
	{
		if( filedata == NULL )
		{
		    size_t hres = 10;
		    FT_Matrix matrix = { (int)((1.0/hres) * 0x10000L),
		                         (int)((0.0)      * 0x10000L),
		                         (int)((0.0)      * 0x10000L),
		                         (int)((1.0)      * 0x10000L) };

			size = 72;
			border = 1;
			gamma = 1.0f;

			if( !dio.isOk() || dio.empty() )
			{
				return false;
			}

			const unsigned int len = dio.getDataSize();

			filedata = new unsigned char[len];

			dio.readBlock( filedata , len );

			FTFontData& ftdata = (*(FTFontData*)data);

			ftdata.error = FT_New_Memory_Face(
						FTSingleton::get().library,
						filedata, // first byte in memory
						len, // size in bytes
						0, // face_index
						&ftdata.face
						);

			if( ftdata.error )
			{
				std::cout << "FT_Error failed to load font " << std::endl;
				delete[] filedata;
				filedata = NULL;
				return false;
			}

		    // Select charmap
			ftdata.error = FT_Select_Charmap( ftdata.face , FT_ENCODING_UNICODE );
		    if( ftdata.error )
		    {
				std::cout << "FT_Error failed to load font: unicode select error " << std::endl;
				delete[] filedata;
				filedata = NULL;
				return false;
		    }


		    // Set char size
		    ftdata.error = FT_Set_Char_Size(
		    		ftdata.face,
		    		0,
		    		size*64,
		    		72*hres,
		    		72 );

		    if( ftdata.error )
		    {
				std::cout << "FT_Error failed to load font: char size select error " << std::endl;
				delete[] filedata;
				filedata = NULL;
				return false;
		    }

		    FT_Set_Transform( ftdata.face, &matrix, NULL );

			atlas.initialize( glm::ivec2( DEFAULT_TEXTURE_SIZE , DEFAULT_TEXTURE_SIZE ) , DEFAULT_TEXTURE_PADDING , ALPHA );

			updateMatrix();

		    return true;
		}

		return false;
	}

	float Font::getSize() const
	{
		return size;
	}

	bool Font::initialize( const std::string filename )
	{
		FileDIO dio;
		dio.open( filename );

		return initialize( dio );
	}

	bool Font::loadSingleGlyph( UNICODE code )
	{
		if( filedata != NULL )
		{
			std::map< UNICODE , Glyph >::iterator iter = glyphs.find( code );

			if( iter != glyphs.end() )
			{
				// Already loaded.
				return true;
			}

			FTFontData& ftdata = (*(FTFontData*)data);
			const unsigned int glyph_index = FT_Get_Char_Index( ftdata.face , code );

			Glyph glyph;

			glyph.setUnicode( code );

			if( glyph_index == 0 )
			{
				glyph.setEmpty( true );
				glyphs[ code ] = glyph;

				return true;
			}

			glyph.setEmpty( false );

			ftdata.error = FT_Load_Glyph( ftdata.face , glyph_index, FT_LOAD_DEFAULT | FT_LOAD_FORCE_AUTOHINT );

			if( ftdata.error )
			{
				std::cout << "FT_Error failed to load glyph:" << std::endl;

				return false;
			}

			// Set rendering, making sure that there is a BITMAP
			if( ftdata.face->glyph->format != FT_GLYPH_FORMAT_BITMAP )
			{
				ftdata.error = FT_Render_Glyph( ftdata.face->glyph, FT_RENDER_MODE_NORMAL );

				if( ftdata.error )
				{
					std::cout << "FT_Error failed to render glyph:" << std::endl;

					return false;
				}
			}

			FT_GlyphSlot slot = ftdata.face->glyph;

			const int real_width = slot->bitmap.width;
			const int real_height = slot->bitmap.rows;
			const int owidth = real_width + 2*border;
			const int oheight = real_height + 2*border;

			if( real_width < 1 || real_height < 1 )
			{
				std::cout << "Font " << code << " is zero sized" << std::endl;
				return false;
			}


			// Gamma correction (sort of)
			// TODO!
//			int x, y;
//			unsigned char c;
//			for( x = 0 ; x < slot->bitmap.width ; ++x )
//			{
//				for( y=0; y < slot->bitmap.rows ; ++y )
//				{
//					c = *(unsigned char *)(slot->bitmap.buffer + y*slot->bitmap.pitch + x );
//					c = (unsigned char) ( pow(c/255.0, gamma) * 255);
//					*(unsigned char *)(slot->bitmap.buffer + y*slot->bitmap.pitch + x ) = c;
//				}
//			}

			unsigned char buffa[ owidth * oheight ];

			memset( buffa , 0 , owidth * oheight *sizeof(unsigned char) );

			int target,source;
			for( int i = real_height - 1 ; i >= 0 ; --i  )
			{
				target = (i * owidth) + border;
				source = (real_height - i - 1) * slot->bitmap.pitch;

				// flip
				memcpy( buffa + target , slot->bitmap.buffer + source , real_width );
			}

			glyph.setTextureSize( glm::ivec2( owidth , oheight ) );

			if( !atlas.request( glyph.getTextureDimensions() , glyph.getTextureLocation() ) )
			{
				atlas.resize( atlas.getDimension() * 2 );
				updateMatrix();

				if( !atlas.request( glyph.getTextureDimensions() , glyph.getTextureLocation() ) )
				{
					std::cout << "FT_Error failed resize atlas." << std::endl;
					return false;
				}
			}

			// Send to texture
			atlas.getTexture().renderSubTexture( glyph.getTextureLocation() , glyph.getTextureDimensions() , buffa );

			// Populate glyph data
			glyph.setSize( glm::vec2( slot->bitmap.width , slot->bitmap.rows ) );
			glyph.setOffset( glm::vec2( slot->bitmap_left , slot->bitmap_top ) );

	        // Discard hinting to get advance
	        FT_Load_Glyph( ftdata.face , glyph_index, FT_LOAD_RENDER | FT_LOAD_NO_HINTING);
			glyph.setAdvance( glm::vec2( ftdata.face->glyph->advance.x / 64.0f , ftdata.face->glyph->advance.y / 64.0f ) );

			// send finally the data
			glyphs[ code ] = glyph;
		}
		return false;
	}

	void Font::cacheGlyphs( std::string utf8text )
	{
		// Parse string, convert to unicode, the glyphs that need converting.
		std::vector<UNICODE> tmp;

		if( utf8tools::decodeTo( utf8text , tmp ) )
		{
			for( unsigned int i = 0 ; i < tmp.size() ; ++i )
			{
				loadSingleGlyph( tmp[i] );
			}
		}
	}

	bool Font::load( const UNICODE glyph )
	{
		return loadSingleGlyph( glyph );
	}

	bool Font::load( const std::vector<UNICODE>& data )
	{
		bool ret = true;

		for( unsigned int i = 0 ; i < data.size() ; ++i )
		{
			if( !loadSingleGlyph( data[i] ) )
			{
				ret = false;
			}
		}

		return ret;
	}

	std::map< UNICODE, Glyph >& Font::getGlyphs()
	{
		return glyphs;
	}

	void Font::bind()
	{
		atlas.getTexture().bind();
	}

	GTexture& Font::getTexture()
	{
		return atlas.getTexture();
	}

	glm::mat4x4& Font::getTextureMatrix()
	{
		return textureMatrix;
	}
}
/* namespace ice */

/* =========================================================================
 * Freetype GL - A C OpenGL Freetype engine
 * Platform:    Any
 * WWW:         http://code.google.com/p/freetype-gl/
 * -------------------------------------------------------------------------
 * Copyright 2011 Nicolas P. Rougier. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  1. Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY NICOLAS P. ROUGIER ''AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL NICOLAS P. ROUGIER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are
 * those of the authors and should not be interpreted as representing official
 * policies, either expressed or implied, of Nicolas P. Rougier.
 * ========================================================================= */
