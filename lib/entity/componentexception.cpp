/*
 * componentexception.cpp
 *
 *  Created on: 6.11.2011
 *      Author: akin
 */

#include "componentexception"

namespace ice {

ComponentException::ComponentException( std::string msg )
: Exception( msg )
{
}

ComponentException::~ComponentException()
{
}

} /* namespace ice */
