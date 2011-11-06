/*
 * threadpool.cpp
 *
 *  Created on: 16.10.2011
 *      Author: akin
 */

#include "threadpool"
#include <fixes/thread>

namespace ice
{

ThreadPool ThreadPool::current;

unsigned int ThreadPool::getHardwareThreadCount()
{
	return std::thread::hardware_concurrency();
}

ThreadPool &ThreadPool::get()
{
	return current;
}

ThreadPool::ThreadPool()
: workers(NULL)
{
}

ThreadPool::~ThreadPool()
{
}

bool ThreadPool::initialize( unsigned int count , std::string loggingProtocol ) throw (ThreadPoolException)
{
	if( workers == NULL )
	{
		worker_count = count;
		workers = new Worker[worker_count];

		for( int i = count - 1 ; i >= 0 ; --i )
		{
			workers[i].init( data , loggingProtocol );
		}

		return true;
	}
	return false;
}

void ThreadPool::kill()
{
	if( workers != NULL )
	{
		for( int i = worker_count - 1 ; i >= 0 ; --i )
		{
			workers[i].terminate();
		}
		delete[] workers;
		workers = NULL;
	}
}

int ThreadPool::getWorkerCount()
{
	return worker_count;
}

void ThreadPool::schedule( Work *work )
{
	data.push( work );
}

}


