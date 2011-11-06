/*
 * pipelineexception.h
 *
 *  Created on: 6.11.2011
 *      Author: akin
 */

#ifndef ICE_PIPELINEEXCEPTION_H_
#define ICE_PIPELINEEXCEPTION_H_

#include <system/exception>

namespace ice
{
	class PipelineException
	{
	public:
		PipelineException( std::string msg );
		virtual ~PipelineException();
	};
} /* namespace ice */
#endif /* PIPELINEEXCEPTION_H_ */
