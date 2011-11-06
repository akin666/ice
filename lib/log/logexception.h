/*
 * logexception.h
 *
 *  Created on: 6.11.2011
 *      Author: akin
 */

#ifndef ICE_LOGEXCEPTION_H_
#define ICE_LOGEXCEPTION_H_

#include <system/exception>

namespace ice
{
	class LogException : public Exception
	{
	public:
		LogException( std::string str );
		virtual ~LogException();
	};
} /* namespace ice */
#endif /* LOGEXCEPTION_H_ */
