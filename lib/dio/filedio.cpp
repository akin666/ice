/*
 * filedio.cpp
 *
 *  Created on: May 12, 2010
 *      Author: akin
 */

#include "filedio"
#include <string>
#include <iostream>

namespace ice
{
	FileDIO::FileDIO()
	{
	}

	FileDIO::FileDIO( std::string path ) throw (DIOException)
	{
		open( path );
	}

	FileDIO::~FileDIO()
	{
		if( stream.is_open() ) {
			stream.close();
		}
	}

	void FileDIO::open( std::string path ) throw (DIOException)
	{
		if( stream.is_open() ) {
			stream.close();
			stream.clear(); // clear bits.
		}

		stream.open( path.c_str() , std::fstream::in | std::fstream::out | std::fstream::binary );

		if( !stream.is_open() ) {
			stream.close();
			throw DIOException( "FileDIO could not open file" );
			return;
		}

		if( !stream.good() ) {
			stream.close();
			throw DIOException( "FileDIO could not open stream" );
			return;
		}
	}

	void FileDIO::readNext()
	{
		// well, im not chunking this one yet
	}

	void FileDIO::lock()
	{
	}

	void FileDIO::unlock()
	{
	}

	int FileDIO::getPosition() throw (DIOException)
	{
		return stream.tellg();
	}

	void FileDIO::setPosition( int position ) throw (DIOException)
	{
		stream.seekg (position, std::ios::beg);
	}

	void FileDIO::forward( int position ) throw (DIOException)
	{
		int pos = stream.tellg();
		stream.seekg (pos + position, std::ios::beg);
	}

	void FileDIO::backward( int position ) throw (DIOException)
	{
		int pos = stream.tellg();
		stream.seekg (pos - position, std::ios::beg);
	}

	bool FileDIO::empty()
	{
		if( !stream.is_open() ) {
			return true;
		}
		if( !stream.good() ) {
			return true;
		}
		return false;
	}

	bool FileDIO::isOk()
	{
		return true;
	}

	void FileDIO::close()
	{
		if( stream.is_open() ) {
			stream.close();
		}
	}

	void FileDIO::refresh()
	{
	}

	void FileDIO::read( float& arg ) throw (DIOException)
	{
		stream.read( (char*)&arg , sizeof(float) );
	}

	void FileDIO::read( char& arg ) throw (DIOException)
	{
		stream.read( (char*)&arg , sizeof(char) );
	}

	void FileDIO::read( unsigned char& arg ) throw (DIOException)
	{
		stream.read( (char*)&arg , sizeof(unsigned char) );
	}

	void FileDIO::read( int& arg ) throw (DIOException)
	{
		stream.read( (char*)&arg , sizeof(int) );
	}

	void FileDIO::read( unsigned int& arg ) throw (DIOException)
	{
		stream.read( (char*)&arg , sizeof(unsigned int) );
	}

	void FileDIO::read( bool& arg ) throw (DIOException)
	{
		stream.read( (char*)&arg , sizeof(bool) );
	}

	void FileDIO::read( std::string& arg ) throw (DIOException)
	{
		stream >> arg;
	}

	void FileDIO::readLine( std::string& arg ) throw (DIOException)
	{
		getline( stream , arg );
	}

	unsigned int FileDIO::readBlock( unsigned char *buffer , const unsigned int char_count ) throw (DIOException)
	{
		stream.read( (char*)buffer , char_count );
		return stream.gcount();
	}

	unsigned int FileDIO::getDataSize()
	{
		int position = stream.tellg();

		stream.seekg (0, std::ios::end);
		int length = stream.tellg();

		stream.seekg (position, std::ios::beg);

		return length - position;
	}

	void FileDIO::writeFloat(const float& arg) throw (DIOException)
	{
		stream.write( (char*)&arg , sizeof(float) );
	}

	void FileDIO::writeByte(const char& arg) throw (DIOException)
	{
		stream.write( (char*)&arg , sizeof(char) );
	}

	void FileDIO::writeByte(const unsigned char& arg) throw (DIOException)
	{
		stream.write( (char*)&arg , sizeof(unsigned char) );
	}

	void FileDIO::writeInt(const int& arg) throw (DIOException)
	{
		stream.write( (char*)&arg , sizeof(int) );
	}

	void FileDIO::writeUnsignedInt(const unsigned int& arg) throw (DIOException)
	{
		stream.write( (char*)&arg , sizeof(unsigned int) );
	}

	void FileDIO::writeBool(const bool& arg) throw (DIOException)
	{
		stream.write( (char*)&arg , sizeof(bool) );
	}

	void FileDIO::writeString(const std::string& arg) throw (DIOException)
	{
		stream << arg.c_str();
	}

	void FileDIO::writeLine(const std::string& arg) throw (DIOException)
	{
		stream << arg.c_str() << std::endl;
	}

	unsigned int FileDIO::writeBlock(const unsigned char *buffer, const unsigned int char_count) throw (DIOException)
	{
		stream.write( (char*)buffer , sizeof(char)*char_count );
		return 0;
	}
}

