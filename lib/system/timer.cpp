/*
 * timer.cpp
 *
 *  Created on: 29.4.2010
 *      Author: akin
 */

#include "timer"

namespace ice
{
Timer::Timer()
{
}

Timer::~Timer()
{
}

void Timer::set( Time time )
{
	val = time;
	reset();
}
void Timer::reset()
{
	to = 0;
}

bool Timer::go()
{
	Time now = clock.getCurrentTime();

	if( to == 0 )
	{
		to = now + val;
	}
	return to > now;
}
}

