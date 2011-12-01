/*
 * microstring.cpp
 *
 *  Created on: 25.11.2011
 *      Author: akin
 */

#include "microstring.h"
#include <cstdio>

MicroString::MicroString( Type type )
: datasize( 0 ),
  data( NULL ),
  dataType( type )
{
}

MicroString::MicroString( const MicroString& other )
: datasize( 0 ),
  data( NULL ),
  dataType( ASCII )
{
	dataType = other.dataType;
	datasize = other.datasize;

	MSSize size = typeSize( dataType ) * datasize;

	if( size > 0 && other.data != NULL )
	{
		data = new char[ size ];
		::memcpy( data , other.data , size );
	}
}

MicroString::MicroString( const char *other , Type type )
: datasize( 0 ),
  data( NULL ),
  dataType( type )
{
	if( other == NULL )
	{
		return;
	}
	size_t tsize = ::strnlen( other , 0xFFF );

	MSSize dtsize = typeSize( dataType );
	if( dtsize < 1 )
	{
		return;

	datasize = tsize / dtsize;
	if( tsize > 0 )
	{
		data = new char[ tsize ];
		::memcpy( data , other , tsize );
	}
}

MicroString::MicroString( int number , Type type )
: datasize( 0 ),
  data( NULL ),
  dataType( type )
{
}

MicroString::MicroString( float number , Type type )
: datasize( 0 ),
  data( NULL ),
  dataType( type )
{
}

MicroString::MicroString( double number , Type type )
: datasize( 0 ),
  data( NULL ),
  dataType( type )
{
}

MicroString::MicroString( bool number , Type type )
: datasize( 0 ),
  data( NULL ),
  dataType( type )
{
}

MicroString::~MicroString()
{
	clear();
}

MSSize MicroString::typeSize( Type type ) const
{
	switch( type )
	{
		case ASCII : return 1;
		case UTF8 : return 1;
		case UTF16 : return 2;
		case UTF32 : return 4;
		case CHAR : return sizeof(char);
		case WCHAR16 : return 2;
		case WCHAR32 : return 4;
	}
	return 0;
}

char *MicroString::CStr()
{
	return data;
}

Type MicroString::type()
{
	return datatype;
}

MSSize MicroString::size()
{
	return datasize;
}

void MicroString::clear()
{
	if( data != NULL )
	{
		delete[] data;
	}
	data = NULL;
	datasize = 0;
}

bool MicroString::operator < ( const MicroString& other ) const
{
	return datasize;
}

bool MicroString::operator > ( const MicroString& other ) const
{
	return datasize;
}

bool MicroString::operator ==( const MicroString& other ) const
{
	return datasize;
}

MicroString& MicroString::operator += ( const MicroString& other )
{
	return datasize;
}

const MicroString MicroString::operator + ( const MicroString& other ) const
{
	MicroString str( *this );
	str += other;
	return str;
}

const MicroString& MicroString::operator = ( const MicroString& other )
{
	MSSize maxsize = other.datasize * typeSize( other.dataType );
	if( datasize > 0 && data != NULL )
	{
		// Some data in already!
		MSSize maxsize
	}
}

