/*
 * textgenerator.h
 *
 *  Created on: 10.7.2011
 *      Author: akin
 */

#ifndef TEXTGENERATOR_H_
#define TEXTGENERATOR_H_

#include "../text/textmesh.h"
#include <font/font.h>
#include <vector>
#include "textformat.h"
#include <datatypes/color.h>

namespace ice
{
	class TextGenerator
	{
	public:
		static bool create( std::vector<UNICODE>& text , Font& font , TextMesh& mesh , Color<float> color , bool bold = false , bool italic = false );
		static bool create( std::vector<UNICODE>& text , TextFormat& format , TextMesh& mesh );
	};
}

#endif /* TEXTGENERATOR_H_ */
