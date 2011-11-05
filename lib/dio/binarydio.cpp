/*
 * binaryreader.cpp
 *
 *  Created on: 17.3.2011
 *      Author: akin
 */

#include "binarydio.h"

namespace ice
{
	BinaryDIO::BinaryDIO()
	{
	}

	BinaryDIO::BinaryDIO( std::string path )
	{
		open( path );
	}

	BinaryDIO::~BinaryDIO()
	{
		if( file != NULL )
		{
			fclose( file );
			file = NULL;
		}
	}

	void BinaryDIO::open( std::string path )
	{
		if( file != NULL )
		{
			fclose( file );
			file = NULL;
		}

		file = fopen( path.c_str() , "rb+" );

		if( file == NULL )
		{
			file = fopen( path.c_str() , "wb+" );

			if( file == NULL )
			{
				std::cout <<"Could not open new file: " << path << std::endl;
			}
		}
	}

	void BinaryDIO::readNext()
	{
		// well, im not chunking this one yet
	}

	void BinaryDIO::lock()
	{
	}

	void BinaryDIO::unlock()
	{
	}

	int BinaryDIO::getPosition()
	{
		return (int)ftell( file );
	}

	void BinaryDIO::setPosition( int position )
	{
		fseek( file , position , SEEK_SET );
	}

	void BinaryDIO::forward( int position )
	{
		fseek( file , position , SEEK_CUR );
	}

	void BinaryDIO::backward( int position )
	{
		fseek( file , position , SEEK_CUR );
	}

	bool BinaryDIO::empty()
	{
		if( file == NULL  )
		{
			return true;
		}
		return false;
	}

	bool BinaryDIO::isOk()
	{
		return file != NULL;
	}

	void BinaryDIO::close()
	{
		if( file != NULL )
		{
			fclose( file );
			file = NULL;
		}
	}

	void BinaryDIO::refresh()
	{
	}

	void BinaryDIO::read( float& arg )
	{
		fread( &arg , sizeof(float) , 1 , file  );
	}

	void BinaryDIO::read( char& arg )
	{
		fread( &arg , sizeof(char) , 1 , file  );
	}

	void BinaryDIO::read( unsigned char& arg )
	{
		fread( &arg , sizeof(unsigned char) , 1 , file  );
	}

	void BinaryDIO::read( int& arg )
	{
		fread( &arg , sizeof(int) , 1 , file  );
	}

	void BinaryDIO::read( unsigned int& arg )
	{
		fread( &arg , sizeof(unsigned int) , 1 , file  );
	}

	void BinaryDIO::read( bool& arg )
	{
		fread( &arg , sizeof(bool) , 1 , file  );
	}

	void BinaryDIO::read( std::string& arg )
	{
		std::cout << "READ STRING NOT SUPPORTED" << std::endl;
	}

	void BinaryDIO::readLine( std::string& arg )
	{
		std::cout << "READ LINE STRING NOT SUPPORTED" << std::endl;
	}

	unsigned int BinaryDIO::readBlock( unsigned char *buffer , const unsigned int char_count )
	{
		return fread( &buffer , sizeof(unsigned char) , char_count , file  );
	}

	unsigned int BinaryDIO::getDataSize()
	{
		const long current_position = ftell( file );
		fseek( file , 0 , SEEK_END );
		const long end_position = ftell( file );
		fseek( file , current_position , SEEK_SET );

		return end_position - current_position;
	}

	void BinaryDIO::writeFloat(const float& arg)
	{
		fwrite( &arg , 1 , sizeof(float) , file );
	}

	void BinaryDIO::writeByte(const char& arg)
	{
		fwrite( &arg , 1 , sizeof(char) , file );
	}

	void BinaryDIO::writeByte(const unsigned char& arg)
	{
		fwrite( &arg , 1 , sizeof(unsigned char) , file );
	}

	void BinaryDIO::writeInt(const int& arg)
	{
		fwrite( &arg , 1 , sizeof(int) , file );
	}

	void BinaryDIO::writeUnsignedInt(const unsigned int& arg)
	{
		fwrite( &arg , 1 , sizeof(unsigned int) , file );
	}

	void BinaryDIO::writeBool(const bool& arg)
	{
		fwrite( &arg , 1 , sizeof(bool) , file );
	}

	void BinaryDIO::writeString(const std::string& arg)
	{
		fputs( arg.c_str() , file );
	}

	void BinaryDIO::writeLine(const std::string& arg)
	{
		fputs( arg.c_str() , file );
	}

	unsigned int BinaryDIO::writeBlock(const unsigned char *buffer, const unsigned int char_count)
	{
		size_t tmp = fwrite( buffer , 1 , sizeof(unsigned char) * char_count , file );
		return (unsigned int)tmp;
	}
}
