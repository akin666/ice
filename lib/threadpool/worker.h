/*
 * worker.h
 *
 *  Created on: 15.10.2011
 *      Author: akin
 */

#ifndef WORKER_H_
#define WORKER_H_

#include <fixes/thread>
#include <string>
#include <log/log>
#include "tque"
#include "threadpoolexception"

namespace ice
{
class WorkQueu;

class Worker
{
protected:
	TQue<Work*> *queu;
	std::thread *thread;

	std::mutex mutex;
	std::condition_variable condition;
	Log log;
	bool going;
public:
	Worker();
	~Worker();

	void init( TQue<Work*>& wqueu , std::string loggingProtocol ) throw (ThreadPoolException);

	void operator()();

	void terminate();
	void wait();
};

} /* namespace ice */
#endif /* WORKER_H_ */
