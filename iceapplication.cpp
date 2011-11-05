/*
 * iceapplication.cpp
 *
 *  Created on: 26.10.2011
 *      Author: akin
 */

#include "iceapplication.h"

#define ICEAPP_RUNNING 		0x0001
#define ICEAPP_REBOOT_REQ  	0x0002
#define ICEAPP_QUIT_REQ		0x0004
#define ICEAPP_ERROR		0x0008
#define ICEAPP_INITIALIZED	0x0010

namespace ice
{

IceApplication::IceApplication( int argc , char *argv[] )
: state( ICEAPP_RUNNING )
{
	processArgs( argc , argv );
}

IceApplication::~IceApplication()
{
}

void IceApplication::initialize( std::string logProtocol , unsigned int pool_worker_count )
{
	if( (state & ICEAPP_INITIALIZED) == 0 )
	{
		if( pool.initialize( pool_worker_count , logProtocol ) )
		{
			state |= ICEAPP_INITIALIZED;
		}
		else
		{
			kill();
		}
	}
}

void IceApplication::suspend()
{
	state &= ~ICEAPP_RUNNING;
}

void IceApplication::resume()
{
	state |= ICEAPP_RUNNING;
}

void IceApplication::kill()
{
	state |= ICEAPP_QUIT_REQ;
}

void IceApplication::restart()
{
	state |= ICEAPP_REBOOT_REQ;
}

void IceApplication::log( std::string msg )
{
}

Time IceApplication::getTime()
{
	return 0;
}

unsigned int IceApplication::getUnixTime()
{
	return 0;
}

ThreadPool& IceApplication::getThreadPool()
{
	return pool;
}

Pipeline& IceApplication::getPipeline()
{
	return pipeline;
}

bool IceApplication::shouldExit()
{
	return (state & ICEAPP_QUIT_REQ) != 0;
}

bool IceApplication::shouldRestart()
{
	return (state & ICEAPP_REBOOT_REQ) != 0;
}

} /* namespace ice */
