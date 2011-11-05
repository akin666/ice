
#ifndef UTF8_DECODE_H_
#define UTF8_DECODE_H_

//
// This library decodes UTF8 std::string to unicode32 (unsigned integer) format.
//

#include <vector>
#include <iostream>
#include "../datatypes/common.h"

namespace ice
{
class UTF8Decoder
{
private:
	unsigned int unicodeLength;
	std::string input;
public:
	UTF8Decoder();
	~UTF8Decoder();

	bool init( const std::string data );
	void reset();

	bool isEmpty();

	bool decodeTo( std::vector<UNICODE>& data );
};
}

#endif

