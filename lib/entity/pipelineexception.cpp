/*
 * pipelineexception.cpp
 *
 *  Created on: 6.11.2011
 *      Author: akin
 */

#include "pipelineexception"

namespace ice
{

PipelineException::PipelineException( std::string msg )
: Exception( msg )
{
}

PipelineException::~PipelineException()
{
}

} /* namespace ice */
