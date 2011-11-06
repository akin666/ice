/*
 * TextFileDIO.h
 *
 *  Created on: 6.3.2011
 *      Author: akin
 */

#ifndef ICE_TEXTFILEDIO_H_
#define ICE_TEXTFILEDIO_H_

#include "dio"
#include <fstream>

namespace ice
{
	class TextFileDIO : public DIO
	{
	protected:
		std::fstream stream;
	public:
		TextFileDIO();
		TextFileDIO( std::string path );
		virtual ~TextFileDIO();

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

#endif /* TEXTFILEDIO_H_ */
