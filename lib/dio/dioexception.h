/*
 * dioexception.h
 *
 *  Created on: 6.11.2011
 *      Author: akin
 */

#ifndef ICE_DIOEXCEPTION_H_
#define ICE_DIOEXCEPTION_H_

#include <system/exception>

namespace ice
{
	class DIOException : public Exception
	{
	public:
		DIOException( std::string msg );
		virtual ~DIOException() throw();
	};

} /* namespace ice */
#endif /* DIOEXCEPTION_H_ */
