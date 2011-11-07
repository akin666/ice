/*
 * dioxception.cpp
 *
 *  Created on: 6.11.2011
 *      Author: akin
 */

#include "dioexception.h"

namespace ice {

DIOException::DIOException( std::string msg )
: Exception( msg )
{
}

DIOException::~DIOException() throw()
{
}

} /* namespace ice */
