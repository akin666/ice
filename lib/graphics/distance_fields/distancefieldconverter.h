/*
 * distancefieldconverter.h
 *
 *  Created on: 27.3.2011
 *      Author: akin
 */

#ifndef DISTANCEFIELDCONVERTER_H_
#define DISTANCEFIELDCONVERTER_H_

namespace ice
{
	class DistanceFieldConverter
	{
	public:
		DistanceFieldConverter();
		virtual ~DistanceFieldConverter();

		static void transform( const unsigned char *src_bitmap ,
						const int src_width,
						const int src_height,
						unsigned char *dst_bitmap,
						const int dst_width,
						const int dst_height,
						const int scale,
						const float spread );
	};
}

#endif /* DISTANCEFIELDCONVERTER_H_ */
