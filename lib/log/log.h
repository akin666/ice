/*
 * clientlog.h
 *
 *  Created on: 6.10.2011
 *      Author: akin
 */

#ifndef ICE_LOG_H_
#define ICE_LOG_H_

#include <string>
#include "logexception"

namespace ice
{
	class Log
	{
	protected:
		void *lg;
	public:
		enum Level {
			Error = 0,
			Warning = 1,
			Notification = 2,
		};

		Log();
		~Log();

		void setProtocol( std::string protocol ) throw (LogException);
		void init() throw (LogException);
		void kill();

		void fire( Level level , std::string data );
	};
} /* namespace ice */
#endif /* ICE_LOG_H_ */
