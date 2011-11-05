/*
 * timer.h
 *
 *  Created on: 29.4.2010
 *      Author: akin
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <datatypes/common.h>

namespace ice
{
class Timer {
protected:
	Time val;
	Time to;
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
