/*
 * textformat.h
 *
 *  Created on: 31.7.2011
 *      Author: akin
 */

#ifndef TEXTFORMAT_H_
#define TEXTFORMAT_H_

#include <datatypes/color.h>
#include <string>

namespace ice
{
	class TextFormat
	{
	protected:
		float pixelHeight;
		Color<float> color;
		bool italic;
		bool bold;
		std::string font;
	public:
		TextFormat();
		TextFormat( const TextFormat& other );
		virtual ~TextFormat();

		void setSize( const float height );
		void setColor( const Color<float>& val );
		void setItalic( const bool val );
		void setBold( const bool val );
		void setFont( const std::string fontName );

		float getSize() const;
		Color<float> getColor() const;
		bool getItalic() const;
		bool getBold() const;
		std::string getFontName() const;
	};
} /* namespace ice */
#endif /* TEXTFORMAT_H_ */
