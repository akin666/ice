/*
 * threadpool.h
 *
 *  Created on: 15.10.2011
 *      Author: akin
 */

#ifndef THREADPOOL_H_
#define THREADPOOL_H_

#include "work"
#include "worker"
#include "tque"
#include "threadpoolexception"

namespace ice
{

class ThreadPool
{
protected:
	TQue<Work*> data;
	Worker *workers;
	int worker_count;

	static ThreadPool current;
public:
	ThreadPool();
	~ThreadPool();

	static unsigned int getHardwareThreadCount();

	bool initialize( unsigned int count , std::string loggingProtocol ) throw (ThreadPoolException);

	void schedule( Work *work );

	int getWorkerCount();

	void kill();

	static ThreadPool &get();
};

} /* namespace ice */
#endif /* THREADPOOL_H_ */
