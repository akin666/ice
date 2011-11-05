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
#include <log/clientlog.h>
#include "tque"

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
	ClientLog log;
	bool going;
public:
	Worker();
	~Worker();

	void init( TQue<Work*>& wqueu , std::string loggingProtocol );

	void operator()();

	void terminate();
	void wait();
};

} /* namespace ice */
#endif /* WORKER_H_ */
