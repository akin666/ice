/*
 * threadpoolexception.h
 *
 *  Created on: 6.11.2011
 *      Author: akin
 */

#ifndef ICE_THREADPOOLEXCEPTION_H_
#define ICE_THREADPOOLEXCEPTION_H_

#include <system/exception>

namespace ice {

	class ThreadPoolException : public Exception
	{
	public:
		ThreadPoolException( std::string msg );
		virtual ~ThreadPoolException();
	};

} /* namespace ice */
#endif /* THREADPOOLEXCEPTION_H_ */

