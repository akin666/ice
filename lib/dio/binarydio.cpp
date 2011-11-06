/*
 * binaryreader.cpp
 *
 *  Created on: 17.3.2011
 *      Author: akin
 */

#include "binarydio"

namespace ice
{
	BinaryDIO::BinaryDIO()
	{
	}

	BinaryDIO::BinaryDIO( std::string path ) throw (DIOException)
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

	void BinaryDIO::open( std::string path ) throw (DIOException)
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
				throw DIOException( "BinaryDIO could not open file" );
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

	int BinaryDIO::getPosition() throw (DIOException)
	{
		return (int)ftell( file );
	}

	void BinaryDIO::setPosition( int position ) throw (DIOException)
	{
		fseek( file , position , SEEK_SET );
	}

	void BinaryDIO::forward( int position ) throw (DIOException)
	{
		fseek( file , position , SEEK_CUR );
	}

	void BinaryDIO::backward( int position ) throw (DIOException)
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

	void BinaryDIO::read( float& arg ) throw (DIOException)
	{
		fread( &arg , sizeof(float) , 1 , file  );
	}

	void BinaryDIO::read( char& arg ) throw (DIOException)
	{
		fread( &arg , sizeof(char) , 1 , file  );
	}

	void BinaryDIO::read( unsigned char& arg ) throw (DIOException)
	{
		fread( &arg , sizeof(unsigned char) , 1 , file  );
	}

	void BinaryDIO::read( int& arg ) throw (DIOException)
	{
		fread( &arg , sizeof(int) , 1 , file  );
	}

	void BinaryDIO::read( unsigned int& arg ) throw (DIOException)
	{
		fread( &arg , sizeof(unsigned int) , 1 , file  );
	}

	void BinaryDIO::read( bool& arg ) throw (DIOException)
	{
		fread( &arg , sizeof(bool) , 1 , file  );
	}

	void BinaryDIO::read( std::string& arg ) throw (DIOException)
	{
		throw DIOException( "Unsupported BinaryDIO::read std::string" );
	}

	void BinaryDIO::readLine( std::string& arg ) throw (DIOException)
	{
		throw DIOException( "Unsupported BinaryDIO::readLine std::string" );
	}

	unsigned int BinaryDIO::readBlock( unsigned char *buffer , const unsigned int char_count ) throw (DIOException)
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

	void BinaryDIO::writeFloat(const float& arg) throw (DIOException)
	{
		fwrite( &arg , 1 , sizeof(float) , file );
	}

	void BinaryDIO::writeByte(const char& arg) throw (DIOException)
	{
		fwrite( &arg , 1 , sizeof(char) , file );
	}

	void BinaryDIO::writeByte(const unsigned char& arg) throw (DIOException)
	{
		fwrite( &arg , 1 , sizeof(unsigned char) , file );
	}

	void BinaryDIO::writeInt(const int& arg) throw (DIOException)
	{
		fwrite( &arg , 1 , sizeof(int) , file );
	}

	void BinaryDIO::writeUnsignedInt(const unsigned int& arg) throw (DIOException)
	{
		fwrite( &arg , 1 , sizeof(unsigned int) , file );
	}

	void BinaryDIO::writeBool(const bool& arg) throw (DIOException)
	{
		fwrite( &arg , 1 , sizeof(bool) , file );
	}

	void BinaryDIO::writeString(const std::string& arg) throw (DIOException)
	{
		fputs( arg.c_str() , file );
	}

	void BinaryDIO::writeLine(const std::string& arg) throw (DIOException)
	{
		fputs( arg.c_str() , file );
	}

	unsigned int BinaryDIO::writeBlock(const unsigned char *buffer, const unsigned int char_count) throw (DIOException)
	{
		size_t tmp = fwrite( buffer , 1 , sizeof(unsigned char) * char_count , file );
		return (unsigned int)tmp;
	}
}
