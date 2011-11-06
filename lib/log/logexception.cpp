/*
 * logexception.cpp
 *
 *  Created on: 6.11.2011
 *      Author: akin
 */

#include "logexception"

namespace ice
{

LogException::LogException( std::string str )
: Exception( str )
{
}

LogException::~LogException()
{
}

} /* namespace ice */
