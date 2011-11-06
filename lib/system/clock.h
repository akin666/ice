/*
 * clock.h
 *
 *  Created on: 6.11.2011
 *      Author: akin
 */

#ifndef ICE_CLOCK_H_
#define ICE_CLOCK_H_

#include "common"
#include <sys/time.h>

namespace ice
{

	class Clock
	{
	protected:
		unsigned int start;
		unsigned int ustart;
		timeval tmpTime;
	public:
		Clock( Time current = 0 );
		Clock( Seconds current , MicroSeconds us );
		virtual ~Clock();

		Time getCurrentTime();
		Time getUnixTime();

		void getCurrentTime( Seconds& s , MicroSeconds& us );
		void getUnixTime( Seconds& s , MicroSeconds& us );
	};

} /* namespace ice */
#endif

