/*
 * textgenerator.cpp
 *
 *  Created on: 10.7.2011
 *      Author: akin
 */

#include "textgenerator.h"
#include <asset/assetmanager.h>

namespace ice
{
	bool TextGenerator::create(
			std::vector<UNICODE>& text ,
			Font& font ,
			TextMesh& mesh ,
			Color<float> color ,
			bool bold ,
			bool italic )
	{
		mesh.vertexes.clear();
		mesh.textureCoordinates.clear();
		mesh.colors.clear();

		// Make sure all glyphs are loaded..

		std::map< UNICODE, Glyph >& glyphs = font.getGlyphs();

		glm::vec2 max;
		glm::vec2 line;

		unsigned int glyphCount = 0;

		/////
		// SCAN
		/////
		std::map< UNICODE, Glyph >::iterator iter;
		UNICODE current;

		line.x = 0;
		line.y = font.getSize();
		for( unsigned int i = 0 ; i < text.size() ; ++i )
		{
			current = text[i];

			if( current == FL_LINE_FEED || current == FL_CARRIAGE_RETURN )
			{
				// CR/LF or LF/CR
				if( text[i+1] == FL_CARRIAGE_RETURN || text[i+1] == FL_LINE_FEED )
				{
					++i;
				}

				line.y += font.getSize();

				max.x = max.x > line.x ? max.x : line.x;
				max.y = max.y > line.y ? max.y : line.y;

				line.x = 0; // reset

				continue;
			}

			iter = glyphs.find( current );

			if( iter == glyphs.end() )
			{
				// not found!
				if( !font.load( current ) )
				{
					// NOT FOUND!
					continue; // shit happens.
				}
				iter = glyphs.find( current );
			}

			if( !iter->second.isEmpty() )
			{
				++glyphCount;
			}

			line.x += iter->second.getAdvance().x;
		}

		/////
		// Setup mesh
		/////
		mesh.vertexes.reserve( glyphCount * 6 );
		mesh.textureCoordinates.reserve( glyphCount * 6 );
		mesh.colors.reserve( glyphCount * 6 );

		mesh.font = &font;


		glm::vec2 tmpVec2;

		glm::vec2 ta;
		glm::vec2 tb;
		glm::vec2 tc;
		glm::vec2 td;

		glm::vec3 pa;
		glm::vec3 pb;
		glm::vec3 pc;
		glm::vec3 pd;

		glm::vec2 convertor;
		glm::vec2 keybo;
		/////
		// Render
		/////
		line.x = 0;
		line.y = font.getSize();
		for( unsigned int i = 0 ; i < text.size() ; ++i )
		{
			current = text[i];

			if( current == FL_LINE_FEED || current == FL_CARRIAGE_RETURN )
			{
				// CR/LF or LF/CR
				if( text[i+1] == FL_CARRIAGE_RETURN || text[i+1] == FL_LINE_FEED )
				{
					++i;
				}

				line.y += font.getSize();
				line.x = 0;

				continue;
			}

			if( current == FL_HORIZONTAL_TAB )
			{
				line.x += font.getSize();
				continue;
			}

			iter = glyphs.find( current );

			if( iter == glyphs.end() )
			{
				// does not exist.
				continue;
			}

			if( !iter->second.isEmpty() )
			{
				// Renderable..
				Glyph& glyph = iter->second;

				// GTexture coordinate calculations:

				td = glyph.getTextureLocation();
				tb = glyph.getTextureLocation() + glyph.getTextureDimensions();

				ta.x = td.x;
				ta.y = tb.y;

				tc.x = tb.x;
				tc.y = td.y;

				// Vertex coordinate calculations
				// & conversion to 3D from 2D.
				convertor = glyph.getOffset();
				convertor.y = -convertor.y;
				convertor += line;
				pd = glm::vec3( convertor.x , convertor.y , 0.0f );

				keybo = glyph.getSize();

				pb = pd + glm::vec3( keybo , 0.0f );

				pa.x = pd.x;
				pa.y = pb.y;

				pc.x = pb.x;
				pc.y = pd.y;

				mesh.vertexes.push_back( pa );
				mesh.vertexes.push_back( pb );
				mesh.vertexes.push_back( pc );
				mesh.vertexes.push_back( pa );
				mesh.vertexes.push_back( pc );
				mesh.vertexes.push_back( pd );

				mesh.textureCoordinates.push_back( td );
				mesh.textureCoordinates.push_back( tc );
				mesh.textureCoordinates.push_back( tb );
				mesh.textureCoordinates.push_back( td );
				mesh.textureCoordinates.push_back( tb );
				mesh.textureCoordinates.push_back( ta );

				mesh.colors.push_back( color );
				mesh.colors.push_back( color );
				mesh.colors.push_back( color );
				mesh.colors.push_back( color );
				mesh.colors.push_back( color );
				mesh.colors.push_back( color );
			}

			line.x += iter->second.getAdvance().x;
		}

		// buffer em.
		mesh.apply();

		return true;
	}

	bool TextGenerator::create( std::vector<UNICODE>& text , TextFormat& format , TextMesh& mesh )
	{
		Font *font = AssetManager<Font>::get( format.getFontName() );

		if( font == NULL )
		{
			// Get defaultfont!
			// !TODO

			if( font == NULL )
			{
				// Default font does not exist!
				return false;
			}
		}

		if( font == NULL )
		{
			// No font!
			return false;
		}

		return create( text , *font , mesh , format.getColor() , format.getBold() , format.getItalic() );
	}
}
