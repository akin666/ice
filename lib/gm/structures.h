/*
 *
 *  Created on: 20.11.2011
 *      Author: akin
 */

#ifndef ICE_GMSTRUCTURES_H_
#define ICE_GMSTRUCTURES_H_

#include <types>
#include "gmfileenum.h"

namespace GmFile
{
	class Header
	{
	public:
		int8 type[8];
		uint32 test;
		uint32 itemCount;
		uint32 dictionaryLength;
		uint32 dictionaryUnpackedLength;
	};

	class String
	{
	public:
		uint16 length;
		uint32 offset;
	};

	class DictionaryItem
	{
	public:
		uint16 type;	// 2
		uint16 flags;	// 2
		uint32 offset;	// 4
		String name;
	};

	class Item
	{
	};
}

#endif /* ICE_GMSTRUCTURES_H_ */
