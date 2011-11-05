/*
 * timer.cpp
 *
 *  Created on: 29.4.2010
 *      Author: akin
 */

#include "timer.h"
#include "plattform.h"

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
	Time now = Plattform::getTime();

	if( to == 0 )
	{
		to = now + val;
	}
	return to > now;
}
}

