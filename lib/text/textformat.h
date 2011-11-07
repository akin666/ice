/*
 * textformat.h
 *
 *  Created on: 31.7.2011
 *      Author: akin
 */

#ifndef TEXTFORMAT_H_
#define TEXTFORMAT_H_

#include <glm/glm>
#include <string>

namespace ice
{
	class TextFormat
	{
	protected:
		float pixelHeight;
		glm::vec4 color;
		bool italic;
		bool bold;
		std::string font;
	public:
		TextFormat();
		TextFormat( const TextFormat& other );
		virtual ~TextFormat();

		void setSize( const float height );
		void setColor( const glm::vec4& val );
		void setItalic( const bool val );
		void setBold( const bool val );
		void setFont( const std::string fontName );

		float getSize() const;
		glm::vec4 getColor() const;
		bool getItalic() const;
		bool getBold() const;
		std::string getFontName() const;
	};
} /* namespace ice */
#endif /* TEXTFORMAT_H_ */
