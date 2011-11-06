
#ifndef ICE_DIO_READER_H_
#define ICE_DIO_READER_H_

#include "dio"
#include <iostream>
#include <vector>

namespace ice
{
	template <class CType>
	CType *readData( DIO& in )
	{
		// read 1 object from DIO & return pointer to the buff
		CType *buffer = new CType;
		unsigned int read = in.readBlock( (unsigned char *)buffer , sizeof(CType) );

		if( read != sizeof(CType) )
		{
			// Error!
			delete buffer;
			return NULL;
		}
		return buffer;
	}

	template <class CType>
	bool readData( DIO& in , CType& data )
	{
		// read 1 object from DIO & return pointer to the buff
		CType buffer;
		unsigned int read = in.readBlock( (unsigned char *)&buffer , sizeof(CType) );
		if( read != sizeof(CType) )
		{
			// Error!
			return false;
		}

		// copy buffer to data
		memcpy( &data , &buffer , sizeof(CType) );

		return true;
	}

	template <class CType>
	bool readData( DIO& in , std::vector<CType>& data , int count )
	{
		// read count number of objects into data vector from DIO
		data.resize( count );

		unsigned int read = in.readBlock( (unsigned char *)&data[0] , sizeof(CType)*count );

		if( read != sizeof(CType) )
		{
			return false;
		}

		return true;
	}
}

#endif

