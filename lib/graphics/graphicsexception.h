/*
 * graphicsexception.h
 *
 *  Created on: 7.11.2011
 *      Author: akin
 */

#ifndef ICE_GRAPHICSEXCEPTION_H_
#define ICE_GRAPHICSEXCEPTION_H_

#include <system/exception>

namespace ice
{
	class GraphicsException : public Exception
	{
	public:
		GraphicsException( std::string info );
		virtual ~GraphicsException() throw();
	};
} /* namespace ice */
#endif /* GRAPHICSEXCEPTION_H_ */
