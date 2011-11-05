/*
 * filedio.h
 *
 *  Created on: May 12, 2010
 *      Author: akin
 */

#ifndef MEMDIO_H_
#define MEMDIO_H_

#include "dataio.h"
#include <vector>

namespace ice
{
	class MemDIO: public DIO
	{
	protected:
		std::vector<unsigned char> *data;
		int iter;
	public:
		MemDIO();
		MemDIO( std::vector<unsigned char> *buffer );
		MemDIO( DIO& buffer );
		virtual ~MemDIO();

		virtual void readNext();
		virtual bool empty();

		virtual bool isOk();

		virtual void close();
		virtual void refresh();

		virtual void lock();
		virtual void unlock();

		virtual int getPosition();
		virtual void setPosition( int position );
		virtual void forward( int position );
		virtual void backward( int position );

		virtual void read( float& arg );
		virtual void read( char& arg );
		virtual void read( unsigned char& arg );
		virtual void read( int& arg );
		virtual void read( unsigned int& arg );
		virtual void read( bool& arg );
		virtual void read( std::string& arg );
		virtual void readLine( std::string& arg );
		virtual unsigned int readBlock( unsigned char *buffer , const unsigned int byte_count );
		virtual unsigned int getDataSize();

		virtual void writeFloat( const float& arg );
		virtual void writeByte( const char& arg );
		virtual void writeByte( const unsigned char& arg );
		virtual void writeInt( const int& arg );
		virtual void writeUnsignedInt( const unsigned int& arg ) = 0;
		virtual void writeBool( const bool& arg );
		virtual void writeString( const std::string& arg );
		virtual void writeLine( const std::string& arg );
		virtual unsigned int writeBlock( const unsigned char *buffer , const unsigned int byte_count );
	};
}

#endif /* MEMDIO_H_ */
