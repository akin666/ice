/*
 * componentexception.h
 *
 *  Created on: 6.11.2011
 *      Author: akin
 */

#ifndef ICE_COMPONENTEXCEPTION_H_
#define ICE_COMPONENTEXCEPTION_H_

#include <system/exception>

namespace ice
{
	class ComponentException : public Exception
	{
	public:
		ComponentException( std::string msg );
		virtual ~ComponentException();
	};
} /* namespace ice */
#endif /* COMPONENTEXCEPTION_H_ */
