/*
 * distancefieldconverter.cpp
 *
 *  Created on: 27.3.2011
 *      Author: akin
 */

#include "distancefieldconverter.h"
#include <cmath>

namespace ice
{
	DistanceFieldConverter::DistanceFieldConverter()
	{
	}

	DistanceFieldConverter::~DistanceFieldConverter()
	{
	}

	// Source/References/Concepts/Ideas:
	// http://labs.qt.nokia.com/2011/07/15/text-rendering-in-the-qml-scene-graph/
	// http://www.valvesoftware.com/publications/2007/SIGGRAPH2007_AlphaTestedMagnification.pdf
	// http://bitsquid.blogspot.com/2010/04/distance-field-based-rendering-of.html
	// http://www.gamedev.net/topic/491938-signed-distance-bitmap-font-tool/
	// http://ghostinthecode.posterous.com/better-contour-rendering
	// http://www.gbuffer.net/vector-textures
	// http://contourtextures.wikidot.com/
	// http://forum.unity3d.com/threads/68647-Scaling-Bitmap-Fonts
	// http://forum.unity3d.com/threads/10348-Distance-Field-Alpha-Testing-Cheap-Smooth-Outlines
	// http://www.horde3d.org/wiki/index.php5?title=Preprocessing_Technique_-_Distance_Field_Vector_Textures
	// http://www.horde3d.org/forums/viewtopic.php?f=1&t=605&view=next
	// http://iphone-3d-programming.labs.oreilly.com/ch07.html
	// http://www.idevgames.com/forums/thread-205.html
	//
	// Note!
	// this was hacked together from some C# code, and as
	// I do not know C#, this whole thing might be blashemy..
	// NOTE!
	// The original source uses floats to represent channels,
	// I use unsigned char arrays to represent channels.
	//

	unsigned char signedDistance(
			const unsigned char *bitmap ,
			const int width,
			const int height,
			int cx,
			int cy,
			float clamp );

	/**
	 * Computes a distance field transform of a high resolution binary source channel
	 * and returns the result as a low resolution channel.
	 * </summary>
	 *
	 * src_bitmap,src_width,src_height
	 * The source channel
	 *
	 * dst_bitmap,dst_width,dst_height
	 * The destination channel
	 *
	 * scale
	 * The amount the source channel will be scaled down.
	 * A value of 8 means the destination image will be 1/8th the size of the source
	 * image.
	 *
	 * spread
	 * The spread in pixels before the distance field clamps to (zero/one). The value
	 * is specified in units of the destination image. The spread in the source image
	 * will be spread*scale_down.
	 */
	/*
	void DistanceFieldConverter::transform( const unsigned char *src_bitmap ,
					const int src_width,
					const int src_height,
					unsigned char *dst_bitmap,
					const int dst_width,
					const int dst_height,
					const int scale,
					const float spread )
	{
		float source_spread = spread * scale;

		// Go through every pixel in dst_image
		int ytmp;
		const int w_diff = (( dst_width * scale ) - dst_width) / 2;
		const int h_diff = (( dst_height * scale ) - dst_height) / 2;

		int virtual_x;
		int virtual_y;

		for( int y = 0 ; y < dst_height ; ++y )
		{
			ytmp = y * dst_width;
			for( int x = 0 ; x < dst_width ; ++x )
			{
				virtual_x = x * scale - w_diff;
				virtual_y = y * scale - h_diff;

				float sd = signedDistance(
						src_bitmap ,
						src_width ,
						src_height ,
						virtual_x + scale/2 ,
						virtual_y + scale/2 ,
						source_spread
						);

				dst_bitmap[ytmp + x] = (unsigned char)((( sd + source_spread ) / ( source_spread * 2 )) * 0xFF);
			}
		}
	}

	#include <cmath>

	float signedDistance(
			const unsigned char *bitmap ,
			const int width,
			const int height,
			int cx,
			int cy,
			float clamp )
	{
		int cd = - 0x7F;
		if( cx > 0 && cy > 0 && cx < width && cy < height )
		{
			cd = (int)(bitmap[cy * width + cx]) - 0x7F;
		}

		int min_x = cx - (int)clamp - 1;
		if( min_x < 0 )
		{
			min_x = 0;
		}

		int max_x = cx + (int)clamp + 1;
		if( max_x >= width )
		{
			max_x = width - 1;
		}

		float distance = clamp;
		int d;

		for( int dy = 0 ; dy <= (int)clamp + 1 ; ++dy )
		{
			if( dy > distance )
			{
				continue;
			}

			if( cy - dy >= 0 )
			{
				int y1 = cy-dy;
				for( int x = min_x ; x <= max_x ; ++x )
				{
					if( x - cx > distance )
					{
						continue;
					}

					d = - 0x7F;
					if( y1 >= 0 && x >= 0 )
					{
						d = (int)(bitmap[y1*width+x]) - 0x7F;
					}
					if( cd * d <= 0 )
					{
						float d2 = (y1 - cy)*(y1 - cy) + (x-cx)*(x-cx);

						if( d2 < distance*distance )
						{
							distance = sqrtf(d2);
						}
					}
				}
			}

			if(dy != 0 && cy+dy < height)
			{
				int y2 = cy + dy;

				for( int x = min_x ; x <= max_x ; ++x )
				{
					if( x - cx > distance )
					{
						continue;
					}

					d = - 0x7F;
					if( y2 >= 0 && x >= 0 )
					{
						d = (int)(bitmap[y2*width+x]) - 0x7F;
					}
					if( cd * d <= 0 )
					{
						float d2 = (y2 - cy)*(y2 - cy) + (x-cx)*(x-cx);

						if( d2 < distance*distance )
						{
							distance = sqrtf(d2);
						}
					}
				}
			}
		}

		// basically return abs( distance ); for float.
		if (cd > 0)
			return distance;
		else
			return -distance;
	}
	/**/
	void DistanceFieldConverter::transform( const unsigned char *src_bitmap ,
					const int src_width,
					const int src_height,
					unsigned char *dst_bitmap,
					const int dst_width,
					const int dst_height,
					const int scale,
					const float radius )
	{
		const float source_radius = radius * scale;

		// Go through every pixel in dst_image
		int ytmp;

		int virtual_x;
		int virtual_y;

		for( int y = 0 ; y < dst_height ; ++y )
		{
			ytmp = y * dst_width;
			virtual_y = (y - radius) * scale;

			for( int x = 0 ; x < dst_width ; ++x )
			{
				virtual_x = (x - radius) * scale;

				unsigned char sd = signedDistance(
						src_bitmap ,
						src_width ,
						src_height ,
						virtual_x ,
						virtual_y ,
						source_radius
						);

				dst_bitmap[ytmp + x] = sd;//(unsigned char) (sd * 0xFF);// (unsigned char)((( sd + source_spread ) / ( source_spread * 2 )) * 0xFF);
			}
		}
	}

	unsigned char signedDistance(
			const unsigned char *bitmap ,
			const int width,
			const int height,
			int cx,
			int cy,
			float radius )
	{
		if( cx < 0 || cy < 0 || cx > width || cy > height ) return 0x00;

		return bitmap[cy*width+cx];

	//	// area that possibly reaches the radius distance
	//	int sx,sy;
	//	int ex,ey;
	//
	//	sx = cx - (int)radius;
	//	sy = cy - (int)radius;
	//	ex = cx + (int)radius;
	//	ey = cy + (int)radius;
	//
	//	 // not seen
	//	if( ex < 0 || ey < 0 || sx > width || sy > height )
	//	{
	//		return 0;
	//	}
	//
	//	if( sx < 0 ) sx = 0;
	//	if( sy < 0 ) sy = 0;
	//	if( ex >= width ) ex = width - 1;
	//	if( ey >= height ) ey = height - 1;
	//
	//	unsigned char val = 0;
	//	unsigned char current = 0;
	//	int tmp;
	//	int tmpx;
	//	int tmpy;
	//	int tt;
	//	const int distance2 = (int)(radius * radius);
	//	const float weight = ((float)0x7F) / distance2;
	//
	//	for( int y = sy ; y < ey ; ++y )
	//	{
	//		if( val == 0x7F ) break;
	//		tmpy = std::abs( (float)(cy - y) );
	//
	//		if( (float)tmpy*weight*(float)0xFF < current )
	//			continue;
	//
	//		tmp = y*width;
	//		for( int x = sx ; x < ex ; ++x )
	//		{
	//			current = bitmap[tmp+x];
	//			if( val < current )
	//			{
	//				// calculate distance
	//				tmpx = std::abs( (float)(cx - x) );
	//
	//				tt = (tmpx*tmpx + tmpy*tmpy) * weight * current;
	//
	//				if( tt > val )
	//				{
	//					val = tt;
	//				}
	//			}
	//		}
	//	}
	//
	//	return val;
	}
}
