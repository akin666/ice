/*
 * TextTextFileDIO.cpp
 *
 *  Created on: 6.3.2011
 *      Author: akin
 */

#include "textfiledio.h"
#include <string>
#include <iostream>
#include "../sys/log.h"

namespace ice
{
	TextFileDIO::TextFileDIO()
	{
	}

	TextFileDIO::TextFileDIO( std::string path )
	{
		open( path );
	}

	TextFileDIO::~TextFileDIO()
	{
		if( stream.is_open() ) {
			stream.close();
		}
	}

	void TextFileDIO::open( std::string path )
	{
		if( stream.is_open() ) {
			stream.close();
		}

		stream.open( path.c_str() , std::fstream::in | std::fstream::out );

		if( !stream.good() ) {
			stream.close();
			LOG_ERROR( "Could not open file." );
			return;
		}
	}

	void TextFileDIO::readNext()
	{
		// well, im not chunking this one yet
	}

	void TextFileDIO::lock()
	{
	}

	void TextFileDIO::unlock()
	{
	}

	int TextFileDIO::getPosition()
	{
		return stream.tellg();
	}

	void TextFileDIO::setPosition( int position )
	{
		stream.seekg (position, std::ios::beg);
	}

	void TextFileDIO::forward( int position )
	{
		int pos = stream.tellg();
		stream.seekg (pos + position, std::ios::beg);
	}

	void TextFileDIO::backward( int position )
	{
		int pos = stream.tellg();
		stream.seekg (pos - position, std::ios::beg);
	}

	bool TextFileDIO::empty()
	{
		if( !stream.is_open() ) {
			return true;
		}
		if( !stream.good() ) {
			return true;
		}
		return false;
	}

	bool TextFileDIO::isOk()
	{
		return true;
	}

	void TextFileDIO::close()
	{
		if( stream.is_open() ) {
			stream.close();
		}
	}

	void TextFileDIO::refresh()
	{
	}

	void TextFileDIO::read( float& arg )
	{
		stream >> arg;
	}

	void TextFileDIO::read( char& arg )
	{
		stream >> arg;
	}

	void TextFileDIO::read( unsigned char& arg )
	{
		stream >> arg;
	}

	void TextFileDIO::read( int& arg )
	{
		stream >> arg;
	}

	void TextFileDIO::read( unsigned int& arg )
	{
		stream >> arg;
	}

	void TextFileDIO::read( bool& arg )
	{
		std::string data;
		stream >> data;

		arg = ( data == "TRUE" );
	}

	void TextFileDIO::read( std::string& arg )
	{
		stream >> arg;
	}

	void TextFileDIO::readLine( std::string& arg )
	{
		stream >> arg;
	}

	unsigned int TextFileDIO::readBlock( unsigned char *buffer , const unsigned int char_count )
	{
		stream.read( (char*)buffer , char_count );
		return stream.gcount();
	}

	unsigned int TextFileDIO::getDataSize()
	{
		int position = stream.tellg();

		stream.seekg (0, std::ios::end);
		int length = stream.tellg();

		stream.seekg (position, std::ios::beg);

		return length - position;
	}

	void TextFileDIO::writeFloat(const float& arg)
	{
		stream << arg;
	}

	void TextFileDIO::writeByte(const char& arg)
	{
		stream << arg;
	}

	void TextFileDIO::writeByte(const unsigned char& arg)
	{
		stream << arg;
	}

	void TextFileDIO::writeInt(const int& arg)
	{
		stream << arg;
	}

	void TextFileDIO::writeUnsignedInt(const unsigned int& arg)
	{
		stream << arg;
	}

	void TextFileDIO::writeBool(const bool& arg)
	{
		stream << (arg?"TRUE":"FALSE");
	}

	void TextFileDIO::writeString(const std::string& arg)
	{
		stream << arg;
	}

	void TextFileDIO::writeLine(const std::string& arg)
	{
		stream << arg.c_str() << std::endl;
	}

	unsigned int TextFileDIO::writeBlock(const unsigned char *buffer, const unsigned int char_count)
	{
		stream.write( (char*)buffer , sizeof(char)*char_count );
		return 0;
	}
}
