/*
 * worker.cpp
 *
 *  Created on: 16.10.2011
 *      Author: akin
 */

#include "work"
#include "worker"
#include <iostream>
#include <fixes/thread>

namespace ice
{

Worker::Worker()
: thread(NULL)
{
}

Worker::~Worker()
{
	if( thread != NULL )
	{
		delete thread;
		thread = NULL;
	}
}

void Worker::init( TQue<Work*>& wqueu , std::string loggingProtocol )  throw (ThreadPoolException)
{
	// This Sync of worker thread, and initializer, ensures that
	// the worker really is initialized after exiting this function.
	// ! If this is not done, the workers probably will get initialized
	// much later..
	std::unique_lock<std::mutex> lock(mutex);

	if( thread != NULL )
	{
		delete thread;
	}

	log.setProtocol( loggingProtocol );

	queu = &wqueu;

	thread = new std::thread( std::ref(*this) );

	// Ensure that the function returns _after_ the thread has fully initialized
	going = false;
	while( !going )
	{
		condition.wait(lock);
	}
}

void Worker::operator()()
{
	// Thread initialization/volatile/sync block
	{
		std::lock_guard<std::mutex> lock(mutex);
		// Todo! whattodo if log fails.
		try	{
			log.init();
		}
		catch( LogException& ex ) {
		}
		catch( ... ) {
		}

		if( queu == NULL )
		{
			return;
		}

		going = true;
		condition.notify_one();
	}

	Work *current;
	while( going )
	{
		current = queu->pop();
		if( current != NULL )
		{
			if( !current->begin() )
			{
				queu->push( current );
				continue;
			}
			current->setLog( &log );
			current->run();
			current->end();
		}
	}
}

void Worker::terminate()
{
	going = false;

	if( thread != NULL )
	{
		delete thread;
	}
}

void Worker::wait()
{
}

}
