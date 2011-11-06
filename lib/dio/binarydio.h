/*
 * binaryreader.h
 *
 *  Created on: 17.3.2011
 *      Author: akin
 */

#ifndef ICE_BINARYREADER_H_
#define ICE_BINARYREADER_H_

#include <iostream>
#include <cstdio>
#include "dio"

namespace ice
{
	class BinaryDIO : public DIO {
	private:
		FILE *file;
	public:
		BinaryDIO();
		BinaryDIO( std::string path ) 					throw (DIOException);
		virtual ~BinaryDIO();

		void open( std::string path ) 					throw (DIOException) ;

		virtual void readNext();
		virtual bool empty();

		virtual bool isOk();

		virtual void close();
		virtual void refresh();

		virtual void lock();
		virtual void unlock();

		virtual unsigned int getDataSize();

		virtual int getPosition() 						throw (DIOException);
		virtual void setPosition( int position ) 		throw (DIOException);
		virtual void forward( int position ) 			throw (DIOException);
		virtual void backward( int position ) 			throw (DIOException);

		virtual void read( float& arg ) 				throw (DIOException);
		virtual void read( char& arg ) 					throw (DIOException);
		virtual void read( unsigned char& arg ) 		throw (DIOException);
		virtual void read( int& arg ) 					throw (DIOException);
		virtual void read( unsigned int& arg ) 			throw (DIOException);
		virtual void read( bool& arg ) 					throw (DIOException);
		virtual void read( std::string& arg ) 			throw (DIOException);
		virtual void readLine( std::string& arg ) 		throw (DIOException);
		virtual unsigned int readBlock(
				unsigned char *buffer ,
				unsigned int byte_count ) 				throw (DIOException);

		virtual void writeFloat( const float& arg ) 	throw (DIOException);
		virtual void writeByte( const char& arg ) 		throw (DIOException);
		virtual void writeByte( const unsigned char& arg ) throw (DIOException);
		virtual void writeInt( const int& arg ) 		throw (DIOException);
		virtual void writeUnsignedInt( const unsigned int& arg ) throw (DIOException);
		virtual void writeBool( const bool& arg ) 		throw (DIOException);
		virtual void writeString( const std::string& arg ) throw (DIOException);
		virtual void writeLine( const std::string& arg ) throw (DIOException);
		virtual unsigned int writeBlock(
				const unsigned char *buffer ,
				unsigned int byte_count ) 				throw (DIOException);
	};
}

#endif /* BINARYREADER_H_ */
