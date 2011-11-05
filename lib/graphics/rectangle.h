/*
 * rectangle.h
 *
 *  Created on: 12.6.2011
 *      Author: akin
 */

#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "common.h"

namespace ice
{
	template<class ctype>
	class Rectangle
	{
	public:
		 ctype first,second;

		 Rectangle()
		 {}

		 Rectangle( const Rectangle<ctype>& other )
		 : first(other.first),
		   second(other.second)
		 {
		 }
	};
}

#endif /* RECTANGLE_H_ */
