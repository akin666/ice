/*
 * dataio.h
 *
 *  Created on: May 11, 2010
 *      Author: akin
 *
 *  Only forward reading!
 */

#ifndef ICE_DATAIO_H_
#define ICE_DATAIO_H_

#include <iostream>
#include "diolocker"
#include "dioreader"
#include "dioexception"

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

		// Returns size of file, if such measure exists.
		virtual unsigned int getDataSize() = 0;

		// All reading and writing can cause an exception
		// ALSO initializes can cause exception.
		virtual int getPosition()  					throw (DIOException) = 0;
		virtual void setPosition( int position ) 	throw (DIOException) = 0;
		virtual void forward( int position ) 		throw (DIOException) = 0;
		virtual void backward( int position ) 		throw (DIOException) = 0;

		virtual void read( float& arg ) 			throw (DIOException) = 0;
		virtual void read( char& arg ) 				throw (DIOException) = 0;
		virtual void read( unsigned char& arg ) 	throw (DIOException) = 0;
		virtual void read( int& arg ) 				throw (DIOException) = 0;
		virtual void read( unsigned int& arg ) 		throw (DIOException) = 0;
		virtual void read( bool& arg ) 				throw (DIOException) = 0;
		virtual void read( std::string& arg ) 		throw (DIOException) = 0;
		virtual void readLine( std::string& arg ) 	throw (DIOException) = 0;
		virtual unsigned int readBlock(
				unsigned char *buffer ,
				unsigned int byte_count ) 	throw (DIOException) = 0;

		virtual void writeFloat( const float& arg ) throw (DIOException) = 0;
		virtual void writeByte( const char& arg ) 	throw (DIOException) = 0;
		virtual void writeByte( const unsigned char& arg ) throw (DIOException) = 0;
		virtual void writeInt( const int& arg ) 	throw (DIOException) = 0;
		virtual void writeUnsignedInt( const unsigned int& arg ) throw (DIOException) = 0;
		virtual void writeBool( const bool& arg ) 	throw (DIOException) = 0;
		virtual void writeString( const std::string& arg ) throw (DIOException) = 0;
		virtual void writeLine( const std::string& arg ) throw (DIOException) = 0;
		virtual unsigned int writeBlock(
				const unsigned char *buffer ,
				unsigned int byte_count ) 			throw (DIOException) = 0;
	};

	class EmptyDIO : public DIO {
		virtual void readNext(){}
		virtual bool empty()  { return true; }

		virtual void close()  {}
		virtual void refresh()  {}

		virtual void lock()  {}
		virtual void unlock()  {}

		virtual bool isOk()  { return false; }

		// Returns size of file, if such measure exists.
		virtual unsigned int getDataSize() { return 0; }

		virtual int getPosition() throw (DIOException) { return 0; }
		virtual void setPosition( int position ) throw (DIOException) {}
		virtual void forward( int position ) throw (DIOException) {}
		virtual void backward( int position ) throw (DIOException) {}

		virtual void read( float& arg ) throw (DIOException) {}
		virtual void read( char& arg ) throw (DIOException) {}
		virtual void read( unsigned char& arg ) throw (DIOException) {}
		virtual void read( int& arg ) throw (DIOException) {}
		virtual void read( unsigned int& arg ) throw (DIOException) {}
		virtual void read( bool& arg ) throw (DIOException) {}
		virtual void read( std::string& arg ) throw (DIOException) {}
		virtual void readLine( std::string& arg ) throw (DIOException) {}
		virtual unsigned int readBlock(
				unsigned char *buffer ,
				unsigned int byte_count ) throw (DIOException) { return 0; }

		virtual void writeFloat( const float& arg ) throw (DIOException) {}
		virtual void writeByte( const char& arg ) throw (DIOException) {}
		virtual void writeByte( const unsigned char& arg ) throw (DIOException) {}
		virtual void writeInt( const int& arg ) throw (DIOException) {}
		virtual void writeUnsignedInt( const unsigned int& arg )  throw (DIOException) {}
		virtual void writeBool( const bool& arg )  throw (DIOException) {}
		virtual void writeString( const std::string& arg )  throw (DIOException) {}
		virtual void writeLine( const std::string& arg )  throw (DIOException) {}
		virtual unsigned int writeBlock(
				const unsigned char *buffer ,
				unsigned int byte_count )  throw (DIOException) { return 0; }
	};
}

#endif /* DATAIO_H_ */
