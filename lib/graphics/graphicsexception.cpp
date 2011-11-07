/*
 * graphicsexception.cpp
 *
 *  Created on: 7.11.2011
 *      Author: akin
 */

#include "graphicsexception"

namespace ice
{

GraphicsException::GraphicsException( std::string info )
: Exception( info )
{
}

GraphicsException::~GraphicsException() throw()
{
}

} /* namespace ice */
