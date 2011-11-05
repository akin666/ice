/*
 * pipeline.h
 *
 *  Created on: 14.10.2011
 *      Author: akin
 */

#ifndef PIPELINE_H_
#define PIPELINE_H_

#include <iostream>
#include <deque>
#include <iterator>
#include <fixes/thread>
#include "componentnet.h"
#include <threadpool/tque>

namespace ice
{

class Component;

class Pipeline
{
private:
	ComponentNet net;
	std::mutex mutex;

	std::deque<ComponentNode*> temp;
	std::deque<ComponentNode*> nonConcurrent;
	std::deque<ComponentNode*> concurrent;
	TQue<ComponentNode*> waitingQue;
public:
	Pipeline();
	virtual ~Pipeline();

	void attach( Component *component );
	void attachNoSort( Component *component );
	void sort( );

	// Run is the heart of the pipeline, it is essentially the main-loop.
	void run();
};

} /* namespace ice */
#endif /* PIPELINE_H_ */
