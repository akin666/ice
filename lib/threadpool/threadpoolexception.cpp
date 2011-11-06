/*
 * threadpoolexception.cpp
 *
 *  Created on: 6.11.2011
 *      Author: akin
 */

#include "threadpoolexception"

namespace ice {

ThreadPoolException::ThreadPoolException( std::string msg )
: Exception( msg )
{
}

ThreadPoolException::~ThreadPoolException()
{
}

} /* namespace ice */
