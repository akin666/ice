/*
 * text.h
 *
 *  Created on: 31.7.2011
 *      Author: akin
 */

#ifndef TEXT_H_
#define TEXT_H_

#include "textmesh.h"
#include "textformat.h"
#include <datatypes/common.h>
#include <vector>

namespace ice
{
	class Text
	{
	protected:
		TextFormat format;
		TextMesh mesh;
		std::vector<UNICODE> text;
	public:
		Text();
		virtual ~Text();

		TextFormat& getFormat();
		void setFormat( const TextFormat& format );

		void setUTF8( std::string val );
		void setText( std::vector<UNICODE> val );
		std::vector<UNICODE>& getText();

		bool generate();

		TextMesh& getMesh();

		void setShader( ShaderProgram *val );
	};
} /* namespace ice */
#endif /* TEXT_H_ */
