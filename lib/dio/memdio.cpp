/*
 * MemDIO.cpp
 *
 *  Created on: May 12, 2010
 *      Author: akin
 */

#include "memdio.h"
#include <string>
#include <iostream>
#include <sstream>
#include <cstring>
#include "../sys/log.h"

namespace ice
{
	MemDIO::MemDIO()
	{
		iter = 0;
		data = new std::vector<unsigned char>;
	}

	MemDIO::MemDIO( std::vector<unsigned char> *buffer )
	{
		iter = 0;
		data = buffer;
	}

	MemDIO::MemDIO( DIO& buffer )
	{
		iter = 0;
		data = new std::vector<unsigned char>;
		data->resize( buffer.getDataSize() );

		unsigned int len = buffer.readBlock( (unsigned char *)&((*data)[0]) , data->size() );
		if( len < data->size() )
		{
			// well read less than.. who cares..
		}
	}

	MemDIO::~MemDIO()
	{
		if( data != NULL ) {
			delete data;
			data = NULL;
		}
	}

	void MemDIO::readNext()
	{
	}

	void MemDIO::lock()
	{
	}

	void MemDIO::unlock()
	{
	}

	int MemDIO::getPosition()
	{
		return iter;
	}

	void MemDIO::setPosition( int position )
	{
		if( position > (int)(data->size()) || position < 0 ) return;
		iter = position;
	}

	void MemDIO::forward( int position )
	{
		setPosition( iter + position );
	}

	void MemDIO::backward( int position )
	{
		setPosition( iter - position );
	}

	bool MemDIO::empty()
	{
		if( (int)(data->size()) <= iter ) {
			return true;
		}
		return false;
	}

	bool MemDIO::isOk()
	{
		return true;
	}

	void MemDIO::close()
	{
		data->resize(0);
	}

	void MemDIO::refresh()
	{
	}

	void MemDIO::read( float& arg )
	{
		if( iter+4 <= (int)(data->size()) )
		{
			int tt;
			read( tt );
			arg = (float)tt;
		}
	}

	void MemDIO::read( char& arg )
	{
		if( iter+1 <= (int)(data->size()) )
		{
			arg = (*data)[iter];

			++iter;
		}
	}

	void MemDIO::read( unsigned char& arg )
	{
		if( iter+1 <= (int)(data->size()) )
		{
			arg = (*data)[iter];

			++iter;
		}
	}

	void MemDIO::read( int& arg )
	{
		if( iter+4 <= (int)(data->size()) )
		{
			unsigned char *tmp = &((*data)[iter]);
			arg =   (tmp[0] & 0xFF) |
					((tmp[1] & 0xFF) << 8) |
					((tmp[2] & 0xFF) << 16) |
					((tmp[3] & 0xFF) << 24);

			iter +=4;
		}
	}

	void MemDIO::read( unsigned int& arg )
	{
		int tmp;
		read( tmp );
		arg = (unsigned int)tmp;
	}

	void MemDIO::read( bool& arg )
	{
		char tmp = (char)arg;
		read( tmp );
	}

	void MemDIO::read( std::string& arg )
	{
		// ?? TODO
	}

	void MemDIO::readLine( std::string& arg )
	{
		// ?? TODO
	}

	unsigned int MemDIO::readBlock( unsigned char *buffer , const unsigned int char_count )
	{
		unsigned int rb = data->size() - iter;
		rb = rb > char_count ? char_count : rb;

		unsigned char *src = &((*data)[iter]);

		std::memcpy( buffer , src , rb );

		iter += rb;

		return rb;
	}

	unsigned int MemDIO::getDataSize()
	{
		return data->size() - iter;
	}

	void MemDIO::writeFloat(const float& arg)
	{
	//	static char data[4];
	//
	//	data[0] = arg >>
	//	stream.write( (char*)&arg , sizeof(float) );
	}

	void MemDIO::writeByte(const char& arg)
	{
	}

	void MemDIO::writeByte(const unsigned char& arg)
	{
	}

	void MemDIO::writeInt(const int& arg)
	{
	}

	void MemDIO::writeUnsignedInt(const unsigned int& arg)
	{
	}

	void MemDIO::writeBool(const bool& arg)
	{
	}

	void MemDIO::writeString(const std::string& arg)
	{
	}

	void MemDIO::writeLine(const std::string& arg)
	{
	}

	unsigned int MemDIO::writeBlock(const unsigned char *buffer, const unsigned int char_count)
	{
		return 0;
	}
}
