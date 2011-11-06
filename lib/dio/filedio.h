/*
 * filedio.h
 *
 *  Created on: May 12, 2010
 *      Author: akin
 */

#ifndef ICE_FILEDIO_H_
#define ICE_FILEDIO_H_

#include "dio"
#include <fstream>

namespace ice
{
	class FileDIO: public DIO
	{
	protected:
		std::fstream stream;
	public:
		FileDIO();
		FileDIO( std::string path ) throw (DIOException);
		virtual ~FileDIO();

		void open( std::string path ) throw (DIOException);

		virtual void readNext();
		virtual bool empty();

		virtual bool isOk();

		virtual void close();
		virtual void refresh();

		virtual void lock();
		virtual void unlock();

		virtual int getPosition() throw (DIOException);
		virtual void setPosition( int position ) throw (DIOException);
		virtual void forward( int position ) throw (DIOException);
		virtual void backward( int position ) throw (DIOException);

		virtual void read( float& arg ) throw (DIOException);
		virtual void read( char& arg ) throw (DIOException);
		virtual void read( unsigned char& arg ) throw (DIOException);
		virtual void read( int& arg ) throw (DIOException);
		virtual void read( unsigned int& arg ) throw (DIOException);
		virtual void read( bool& arg ) throw (DIOException);
		virtual void read( std::string& arg ) throw (DIOException);
		virtual void readLine( std::string& arg ) throw (DIOException);
		virtual unsigned int readBlock(
				unsigned char *buffer ,
				unsigned int byte_count ) throw (DIOException);

		virtual unsigned int getDataSize();

		virtual void writeFloat( const float& arg ) throw (DIOException);
		virtual void writeByte( const char& arg ) throw (DIOException);
		virtual void writeByte( const unsigned char& arg ) throw (DIOException);
		virtual void writeInt( const int& arg ) throw (DIOException);
		virtual void writeUnsignedInt( const unsigned int& arg ) throw (DIOException);
		virtual void writeBool( const bool& arg ) throw (DIOException);
		virtual void writeString( const std::string& arg ) throw (DIOException);
		virtual void writeLine( const std::string& arg ) throw (DIOException);
		virtual unsigned int writeBlock(
				const unsigned char *buffer ,
				unsigned int byte_count ) throw (DIOException);
	};
}

#endif /* FILEDIO_H_ */
