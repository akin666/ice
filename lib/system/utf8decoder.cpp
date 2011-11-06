/* utf8_decode.c */

/* 2009-02-13 */

/*
Copyright (c) 2005 JSON.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

The Software shall be used for Good, not Evil.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
/*
 * Forked from jSon stuff, still..
 * not doing evil..
 * well the license stays.
 * just converted it to c++
 */

#include "utf8decoder"

#define UTF8_OK   0
#define UTF8_END   -1
#define UTF8_ERROR -2

/*
    Very Strict UTF-8 Decoder

    UTF-8 is a multibyte character encoding of Unicode. A character can be
    represented by 1-4 bytes. The bit pattern of the first byte indicates the
    number of continuation bytes.

    Most UTF-8 decoders tend to be lenient, attempting to recover as much
    information as possible, even from badly encoded input. This UTF-8
    decoder is not lenient. It will reject input which does not include
    proper continuation bytes. It will reject aliases (or suboptimal
    codings). It will reject surrogates. (Surrogate encoding should only be
    used with UTF-16.)

    Code     Contination Minimum Maximum
    0xxxxxxx           0       0     127
    10xxxxxx       error
    110xxxxx           1     128    2047
    1110xxxx           2    2048   65535 excluding 55296 - 57343
    11110xxx           3   65536 1114111
    11111xxx       error
*/

int get( const std::string& data , unsigned int& val , unsigned int& iter , unsigned int& total )
{
	if (iter >= total)
	{
		return UTF8_END;
	}

	val = data.c_str()[iter] & 0xFF;
	++iter;
	return UTF8_OK;
}

int cont( const std::string& data , unsigned int& val , unsigned int& iter , unsigned int& total )
{
	unsigned int c;
	int error = get( data , c , iter , total );
	if( error < UTF8_OK )
	{
		return UTF8_ERROR;
	}
	val = (c & 0x3F);
	return ((c & 0xC0) == 0x80) ? UTF8_OK : UTF8_ERROR;
}

namespace ice
{
UTF8Decoder::UTF8Decoder()
: unicodeLength(0), input("")
{
}

UTF8Decoder::~UTF8Decoder()
{
}

bool UTF8Decoder::init( const std::string data )
{
	input = data;

	// calculate unicode length.
	unicodeLength = 0;
	unsigned int iter = 0;
	unsigned int total = data.size();

	unsigned int c;
	int error;
	while( true )
	{
		if( iter >= total )
		{
			if( iter == total )
			{
				// All ok!
				return true;
			}
			// Error
			break;
		}

		error = get( input , c , iter , total );

		// Zero continuation (0 to 127)
		// 1byte glyph
		if ((c & 0x80) == 0)
		{
			++unicodeLength;
			continue;
		}

		// One contination (128 to 2047)
		// 2byte glyph
		if ((c & 0xE0) == 0xC0)
		{
			iter += 1;
			++unicodeLength;
			continue;
		}

		// Two continuation (2048 to 55295 and 57344 to 65535)
		// 3byte glyph
		if ((c & 0xF0) == 0xE0)
		{
			iter += 2;
			++unicodeLength;
			continue;
		}

		// Three continuation (65536 to 1114111)
		// 4byte glyph
		if ((c & 0xF8) == 0xF0)
		{
			iter += 3;
			++unicodeLength;
			continue;
		}
		break;
	}

	unicodeLength = 0;
	return false;
}

void UTF8Decoder::reset()
{
	input = "";
	unicodeLength = 0;
}

bool UTF8Decoder::isEmpty()
{
	return unicodeLength < 1;
}

bool UTF8Decoder::decodeTo( std::vector<UNICODE>& target )
{
	unsigned int unicodeIter = 0;
	unsigned int iter = 0;
	unsigned int total = input.size();

	if( unicodeLength < 1 )
	{
		target.resize( 0 );
		return false;
	}
	target.resize( unicodeLength );

	unsigned int c,c1,c2,c3,r;
	int error;
	while( true )
	{
		// Reading complete?
		if( iter >= total )
		{
			if( iter == total && unicodeIter == unicodeLength )
			{
				return true;
			}
			// Some data is erronouos
			break;
		}

		error = get( input , c , iter , total );

		// Zero continuation (0 to 127)
		// 1byte glyph
		if ((c & 0x80) == 0)
		{
			target[unicodeIter] = c;
			unicodeIter += 1;
			continue;
		}

		// One contination (128 to 2047)
		// 2byte glyph
		if ((c & 0xE0) == 0xC0)
		{
			error = cont( input , c1 , iter , total );
			if (error < 0)
			{
				// error
				break;
			}
			r = ((c & 0x1F) << 6) | c1;

			if( r >= 128 )
			{
				target[unicodeIter] = r;
				unicodeIter += 1;
				continue;
			}
			// error
			break;
		}

		// Two continuation (2048 to 55295 and 57344 to 65535)
		// 3byte glyph
		if ((c & 0xF0) == 0xE0)
		{
			error = cont( input , c1 , iter , total );
			error += cont( input , c2 , iter , total );
			if (error < 0)
			{
				// error
				break;
			}
			r = ((c & 0x0F) << 12) | (c1 << 6) | c2;

			if( r >= 2048 && (r < 55296 || r > 57343) )
			{
				target[unicodeIter] = r;
				unicodeIter += 1;
				continue;
			}
			// error
			break;
		}

		// Three continuation (65536 to 1114111)
		// 4byte glyph
		if ((c & 0xF8) == 0xF0)
		{
			error = cont( input , c1 , iter , total );
			error+= cont( input , c2 , iter , total );
			error+= cont( input , c3 , iter , total );
			if (error < 0)
			{
				// error
				break;
			}
			r = ((c & 0x0F) << 18) | (c1 << 12) | (c2 << 6) | c3;

			if( r >= 65536 && r <= 1114111 )
			{
				target[unicodeIter] = r;
				unicodeIter += 1;
				continue;
			}
			// error
			break;
		}
		// error
		break;
	}

	// Some error occured.
	target.resize(0);
	return false;
}
}

