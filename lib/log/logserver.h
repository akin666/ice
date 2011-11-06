/*
 * logserver.h
 *
 *  Created on: 1.10.2011
 *      Author: akin
 */

#ifndef ICE_LOGSERVER_H_
#define ICE_LOGSERVER_H_

#include <string>
#include "logexception"

namespace ice
{
	class LogServer
	{
	protected:
		void *server;
	public:
		LogServer();
		virtual ~LogServer();

		void init( std::string filename , std::string protocol ) throw (LogException);
		void kill();
	};
} /* namespace ice */
#endif /* ICE_LOGSERVER_H_ */
