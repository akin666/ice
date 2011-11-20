/*
 * gmfileenum.h
 *
 *  Created on: 20.11.2011
 *      Author: akin
 */

#ifndef GMFILEENUM_H_
#define GMFILEENUM_H_

namespace GmFile
{
	enum ItemType
	{
		GM_NULL 			= 0,			// NULL 				: stuff inside is ignored completely.
		GM_RES 				= 0x0040,		// NULL,RES 			: Reserved.
		GM_Corporate 		= 0x00FF,		// RES,Corporate		: Area reserved for all sorts of corporate unstandard fetishes.
		GM_Runtime_END		= 0x0200, 		// Corporate,Runtime	: Special area that could be used dynamically in program at runtime.
		GM_Start			= 0x0201,
		GM_Container		= GM_Start + 0,
		GM_Font				= GM_Start + 1,
		GM_Texture			= GM_Start + 2,
		GM_Sprite			= GM_Start + 3,
		GM_Script			= GM_Start + 4,
		GM_Config			= GM_Start + 5,
		GM_Text				= GM_Start + 6,
		GM_Copyright		= GM_Start + 7,
		GM_SubTexture		= GM_Start + 8,
		GM_TextureContainer	= GM_Start + 9,
		GM_SpriteContainer 	= GM_Start + 10,
		GM_SpriteTimeline  	= GM_Start + 11,
		GM_MAX				= 0xFFFF
	};


	enum ColorFormat
	{
		RGBA8888		= 1,
		BGRA8888		= 2,
		ALPHA			= 3,
		RED				= 4,
		GREEN			= 5,
		BLUE			= 6,
        LUMINANCE       = 7,
		RGB888			= 8,
		ARGB8888		= 9,
		RGB565			= 10,
	};
}

#endif /* GMFILEENUM_H_ */
