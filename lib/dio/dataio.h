/*
 * dataio.h
 *
 *  Created on: May 11, 2010
 *      Author: akin
 *
 *  Only forward reading!
 */

#ifndef DATAIO_H_
#define DATAIO_H_

#include <iostream>
#include "diolocker.h"

namespace ice
{
	class EmptyDIO;

	class DIO {
	public:
		static EmptyDIO NullDIO;

		virtual ~DIO() {}

		virtual void readNext() = 0;
		virtual bool empty() = 0;

		virtual void close() = 0;
		virtual void refresh() = 0;

		virtual void lock() = 0;
		virtual void unlock() = 0;

		virtual bool isOk() = 0;

		virtual int getPosition() = 0;
		virtual void setPosition( int position ) = 0;
		virtual void forward( int position ) = 0;
		virtual void backward( int position ) = 0;

		virtual void read( float& arg ) = 0;
		virtual void read( char& arg ) = 0;
		virtual void read( unsigned char& arg ) = 0;
		virtual void read( int& arg ) = 0;
		virtual void read( unsigned int& arg ) = 0;
		virtual void read( bool& arg ) = 0;
		virtual void read( std::string& arg ) = 0;
		virtual void readLine( std::string& arg ) = 0;
		virtual unsigned int readBlock( unsigned char *buffer , const unsigned int byte_count ) = 0;

		// Returns size of file, if such measure exists.
		virtual unsigned int getDataSize() = 0;

		virtual void writeFloat( const float& arg ) = 0;
		virtual void writeByte( const char& arg ) = 0;
		virtual void writeByte( const unsigned char& arg ) = 0;
		virtual void writeInt( const int& arg ) = 0;
		virtual void writeUnsignedInt( const unsigned int& arg ) = 0;
		virtual void writeBool( const bool& arg ) = 0;
		virtual void writeString( const std::string& arg ) = 0;
		virtual void writeLine( const std::string& arg ) = 0;
		virtual unsigned int writeBlock( const unsigned char *buffer , const unsigned int byte_count ) = 0;
	};

	class EmptyDIO : public DIO {
		virtual void readNext(){}
		virtual bool empty()  { return true; }

		virtual void close()  {}
		virtual void refresh()  {}

		virtual void lock()  {}
		virtual void unlock()  {}

		virtual bool isOk()  { return false; }

		virtual int getPosition()  { return 0; }
		virtual void setPosition( int position )  {}
		virtual void forward( int position )  {}
		virtual void backward( int position )  {}

		virtual void read( float& arg )  {}
		virtual void read( char& arg )  {}
		virtual void read( unsigned char& arg )  {}
		virtual void read( int& arg )  {}
		virtual void read( unsigned int& arg )  {}
		virtual void read( bool& arg )  {}
		virtual void read( std::string& arg )  {}
		virtual void readLine( std::string& arg )  {}
		virtual unsigned int readBlock( unsigned char *buffer , const unsigned int byte_count )  { return 0; }

		// Returns size of file, if such measure exists.
		virtual unsigned int getDataSize()  { return 0; }

		virtual void writeFloat( const float& arg )  {}
		virtual void writeByte( const char& arg )  {}
		virtual void writeByte( const unsigned char& arg )  {}
		virtual void writeInt( const int& arg )  {}
		virtual void writeUnsignedInt( const unsigned int& arg )  {}
		virtual void writeBool( const bool& arg )  {}
		virtual void writeString( const std::string& arg )  {}
		virtual void writeLine( const std::string& arg )  {}
		virtual unsigned int writeBlock( const unsigned char *buffer , const unsigned int byte_count )  { return 0; }
	};
}

#endif /* DATAIO_H_ */
