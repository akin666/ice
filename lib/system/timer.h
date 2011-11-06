/*
 * timer.h
 *
 *  Created on: 29.4.2010
 *      Author: akin
 *
 *      TODO!
 *      wtf is this calss?
 */

#ifndef ICE_TIMER_H_
#define ICE_TIMER_H_

#include "common"
#include "clock"

namespace ice
{
	class Timer
	{
	protected:
		Time val;
		Time to;
		Clock clock;
	public:
		Timer();
		virtual ~Timer();

		void set( Time time );

		void reset();

		bool go();
	};

#ifdef COMMENTS
So this thing is supposed to work as:

{
  ...
  Timer timer;

  timer.set( 100 );

  while( timer.go() ) {
    doSmallTasks();
  }
  ...
}
#endif
}

#endif /* TIMER_H_ */
