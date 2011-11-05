/*
 * filedio.h
 *
 *  Created on: May 12, 2010
 *      Author: akin
 */

#ifndef FILEDIO_H_
#define FILEDIO_H_

#include "dataio.h"
#include <fstream>

namespace ice
{
	class FileDIO: public DIO
	{
	protected:
		std::fstream stream;
	public:
		FileDIO();
		FileDIO( std::string path );
		virtual ~FileDIO();

		void open( std::string path );

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
		virtual void writeUnsignedInt( const unsigned int& arg );
		virtual void writeBool( const bool& arg );
		virtual void writeString( const std::string& arg );
		virtual void writeLine( const std::string& arg );
		virtual unsigned int writeBlock( const unsigned char *buffer , const unsigned int byte_count );
	};
}

#endif /* FILEDIO_H_ */
