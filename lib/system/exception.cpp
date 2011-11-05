/*
 * exception.cpp
 *
 *  Created on: Jan 31, 2010
 *      Author: akin
 */

#include "exception"

namespace ice
{
        Exception::Exception( std::string msg )
        : message(msg)
	{
	}

        Exception::Exception( const Exception& other )
        : message( other.message )
        {
        }

        Exception::~Exception() throw()
	{
	}

        std::string Exception::getMessage()
        {
            return message;
        }
}
